/* Pinos
 * Copyright (C) 2015 Wim Taymans <wim.taymans@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include <pinos/server/core.h>
#include <pinos/server/data-loop.h>

typedef struct {
  PinosCore  this;

  GDBusObjectManagerServer *server_manager;

  SpaSupport support[4];

} PinosCoreImpl;

PinosCore *
pinos_core_new (PinosMainLoop *main_loop)
{
  PinosCoreImpl *impl;
  PinosCore *this;

  impl = calloc (1, sizeof (PinosCoreImpl));
  this = &impl->this;
  pinos_registry_init (&this->registry);

  this->data_loop = pinos_data_loop_new ();
  this->main_loop = main_loop;

  impl->support[0].uri = SPA_ID_MAP_URI;
  impl->support[0].data = this->registry.map;
  impl->support[1].uri = SPA_LOG_URI;
  impl->support[1].data = pinos_log_get ();
  impl->support[2].uri = SPA_POLL__DataLoop;
  impl->support[2].data = &this->data_loop->poll;
  impl->support[3].uri = SPA_POLL__MainLoop;
  impl->support[3].data = this->main_loop->poll;
  this->support = impl->support;
  this->n_support = 4;

  spa_list_init (&this->global_list);
  spa_list_init (&this->client_list);
  spa_list_init (&this->node_list);
  spa_list_init (&this->node_factory_list);
  spa_list_init (&this->link_list);
  pinos_signal_init (&this->destroy_signal);
  pinos_signal_init (&this->global_added);
  pinos_signal_init (&this->global_removed);
  pinos_signal_init (&this->node_state_changed);
  pinos_signal_init (&this->port_added);
  pinos_signal_init (&this->port_removed);
  pinos_signal_init (&this->port_unlinked);
  pinos_signal_init (&this->link_state_changed);
  pinos_signal_init (&this->node_unlink);
  pinos_signal_init (&this->node_unlink_done);

  return this;
}

void
pinos_core_destroy (PinosCore *core)
{
  PinosCoreImpl *impl = SPA_CONTAINER_OF (core, PinosCoreImpl, this);

  pinos_signal_emit (&core->destroy_signal, core);

  pinos_data_loop_destroy (core->data_loop);

  free (impl);
}

PinosGlobal *
pinos_core_add_global (PinosCore           *core,
                       uint32_t             type,
                       void                *object,
                       PinosObjectSkeleton *skel)
{
  PinosGlobal *global;

  global = calloc (1, sizeof (PinosGlobal));
  global->core = core;
  global->id = 0;
  global->type = type;
  global->object = object;
  global->skel = skel;

  pinos_signal_init (&global->destroy_signal);

  spa_list_insert (core->global_list.prev, &global->link);
  pinos_signal_emit (&core->global_added, core, global);

  return global;
}

void
pinos_core_remove_global (PinosCore      *core,
                          PinosGlobal    *global)
{
  pinos_signal_emit (&global->destroy_signal, global);

  spa_list_remove (&global->link);
  pinos_signal_emit (&core->global_removed, core, global);

  g_clear_object (&global->skel);

  free (global);
}
