/*
 * libmanyuc - Template specifications file
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

#ifndef TEMPLATE_COMMON_H
#define TEMPLATE_COMMON_H

/* Macros and declarations needed for this port */
#ifdef __cplusplus
extern "C" {
#endif

// Typedefs
    typedef enum InternalPinName {
        ARM_PA0, ARM_PA1, ARM_PA2, ARM_PA3, ARM_PA4, ARM_PA5, ARM_PA6, ARM_PA7, 
        ARM_PA8, ARM_PA9, ARM_PA10, ARM_PA11, ARM_PA12, ARM_PA13, ARM_PA14, ARM_PA15, 
        ARM_PB0, ARM_PB1, ARM_PB2, ARM_PB3, ARM_PB4, ARM_PB5, ARM_PB6, ARM_PB7, 
        ARM_PB8, ARM_PB9, ARM_PB10, ARM_PB11, ARM_PB12, ARM_PB13, ARM_PB14, ARM_PB15, 
        ARM_PC0, ARM_PC1, ARM_PC2, ARM_PC3, ARM_PC4, ARM_PC5, ARM_PC6, ARM_PC7, 
        ARM_PC8, ARM_PC9, ARM_PC10, ARM_PC11, ARM_PC12, ARM_PC13, ARM_PC14, ARM_PC15, 
        ARM_PD0, ARM_PD1, ARM_PD2, ARM_PD3, ARM_PD4, ARM_PD5, ARM_PD6, ARM_PD7, 
        ARM_PD8, ARM_PD9, ARM_PD10, ARM_PD11, ARM_PD12, ARM_PD13, ARM_PD14, ARM_PD15, 
        ARM_PE0, ARM_PE1, ARM_PE2, ARM_PE3, ARM_PE4, ARM_PE5, ARM_PE6, ARM_PE7, 
        ARM_PE8, ARM_PE9, ARM_PE10, ARM_PE11, ARM_PE12, ARM_PE13, ARM_PE14, ARM_PE15, 
        ARM_PF0, ARM_PF1, ARM_PF2, ARM_PF3, ARM_PF4, ARM_PF5, ARM_PF6, ARM_PF7, 
        ARM_PF8, ARM_PF9, ARM_PF10, ARM_PF11, ARM_PF12, ARM_PF13, ARM_PF14, ARM_PF15, 
        ARM_PG0, ARM_PG1, ARM_PG2, ARM_PG3, ARM_PG4, ARM_PG5, ARM_PG6, ARM_PG7, 
        ARM_PG8, ARM_PG9, ARM_PG10, ARM_PG11, ARM_PG12, ARM_PG13, ARM_PG14, ARM_PG15, 
        ARM_PH0, ARM_PH1, ARM_PH2, ARM_PH3, ARM_PH4, ARM_PH5, ARM_PH6, ARM_PH7, 
        ARM_PH8, ARM_PH9, ARM_PH10, ARM_PH11, ARM_PH12, ARM_PH13, ARM_PH14, ARM_PH15, 
        ARM_PI0, ARM_PI1, ARM_PI2, ARM_PI3, ARM_PI4, ARM_PI5, ARM_PI6, ARM_PI7, 
        ARM_PI8, ARM_PI9, ARM_PI10, ARM_PI11, ARM_PI12, ARM_PI13, ARM_PI14, ARM_PI15, 
    } InternalPinName;

    typedef enum PinMode
    {
        // Input Modes
        PullNone = 0, PullUp = 1, PullDown = 2,
        // OpenDrain vs. NormalMode
        OpenDrain = 4, NormalMode = 5,
        // Input/Output Modes
        Output = 8, Input = 9,
        // Alternate Pin Functions
        Alt0 = 16, Alt1, Alt2, Alt3, Alt4, Alt5, Alt6, Alt7
        Alt8, Alt9, Alt10, Alt11, Alt12, Alt13, Alt14, Alt15
    } PinMode;

    typedef enum IOIntMode
    {
        IOIntRise, IOIntFall, IOIntRiseFall
    } IOIntMode;

    typedef enum AnalogInMode
    {
    } AnalogInMode;

// **********
// Structures
// **********

// Pin structure to hold port and address
    struct _pin_t
    {
        uint8_t port;
        uint8_t address;
        uint32_t mask;
    };

// Port structure for buses
    typedef struct Port_t
    {
    } Port_t;

// Bus structure
    struct _pinBus_t
    {
    };

// Serial port structure to hold all port info
    struct _serial_t
    {
        STM_USART_TypeDef *uart;
        uint32_t number;
    };

// PWM structure
    struct _pwm_pin_t
    {
    };

// Scheduler structure
    struct _scheduler_t
    {
    };

// I2C structure
    struct _i2c_t
    {
    };

// AnalogIn structure
    struct _analog_in_t
    {
    };

#include "inline.c"

#ifdef __cplusplus
}
#endif

#endif
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
