/* Simple Plugin API
 *
 * Copyright © 2018 Wim Taymans
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef __SPA_CONTROL_TYPES_H__
#define __SPA_CONTROL_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <spa/utils/defs.h>
#include <spa/utils/type-info.h>
#include <spa/control/control.h>

/* base for parameter object enumerations */
#define SPA_TYPE__Control		SPA_TYPE_ENUM_BASE "Control"
#define SPA_TYPE_CONTROL_BASE		SPA_TYPE__Control ":"

static const struct spa_type_info spa_type_control[] = {
	{ SPA_CONTROL_Invalid, SPA_TYPE_CONTROL_BASE "Invalid", SPA_TYPE_Int, },
	{ SPA_CONTROL_Properties, SPA_TYPE_CONTROL_BASE "Properties", SPA_TYPE_Int, },
	{ SPA_CONTROL_Midi, SPA_TYPE_CONTROL_BASE "Midi", SPA_TYPE_Int, },
	{ 0, NULL, },
};

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* __SPA_CONTROL_TYPES_H__ */