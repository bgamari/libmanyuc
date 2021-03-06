/*
 * libmanyuc - main header file
 * Copyright (C) 2012 - Margarita Manterola Rivero
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA
 */

#ifndef __LIBMANYUC_H
#define __LIBMANYUC_H

#ifdef __cplusplus
extern "C" {
#endif

// Definitions
#include "port.h"

// Port specific functions
#include "io.h"
#include "adc.h"
#include "pwm.h"
#include "serial.h"
#include "timers.h"
#include "i2c.h"

// Arch independent functions
#include "hash.h"
#include "swtimer.h"

#ifdef __cplusplus
}
#include "libmanyuc_cpp.h"
#endif

#endif
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
