/*
 * libmanyuc - STM32 udaq specifications file
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

#ifndef UDAQ_BOARD_H
#define UDAQ_BOARD_H

/* Macros and declarations needed for this port */

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

    // Names of the Pins
    typedef enum PinName {

        A0 = ARM_PA0,
        A1 = ARM_PA1,

        // Extra pins
        LED1 = ARM_PC15,
        LED2 = ARM_PC0,
        LED3 = ARM_PC1,
        LED4 = LED1,

    }
    PinName;

#ifdef __cplusplus
}
#endif

#endif
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
