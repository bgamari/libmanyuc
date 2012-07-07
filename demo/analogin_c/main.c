/*
 * libmanyuc - Turn leds on in C example
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

#include "libmanyuc.h"
#include <stdio.h>
#include <stdlib.h>

/* This example reads two sensors, using the ADC3 and ADC4.
   To do that, the pins in P9 and P10 have to be turned on. The pins
   P20 and P30 are turned on or off according to the value. When the
   DEBUG compiling flag is set, the output read is sent through the
   serial port as well.
*/

inline unsigned int show_adc_with_light(AnalogIn_t in, Pin_t light) {
    unsigned int value = AnalogIn_Read(in, ADC_NORMAL);
    // A small number means white
    if (value < 2000) {
        Pin_On(light);
    } else {
        Pin_Off(light);
    }
    return value;
}

int main(void) {

#ifdef DEBUG
    Serial_t port = Serial_Init(0, 9600);
    char cadena[10];
#endif

    AnalogIn_t p = AnalogIn_Init(ADC4);
    AnalogIn_t q = AnalogIn_Init(ADC3);

    Pin_t sensor1 = Pin_Init(P9, 1, Output);
    Pin_t sensor2 = Pin_Init(P10, 1, Output);

    Pin_t light1 = Pin_Init(P20, 1, Output);
    Pin_t light2 = Pin_Init(P30, 1, Output);

    Pin_On(sensor1);
    Pin_On(sensor2);

    while (1) {
        unsigned int s1 = show_adc_with_light(p, light1);
        unsigned int s2 = show_adc_with_light(q, light2);

#ifdef DEBUG
        // Send the value through the serial port
        snprintf(cadena, 10, "1: %d\r\n", s1);
        Serial_Put_Bytes(port, BLOCKING, cadena, 9);
        // Send the value through the serial port
        snprintf(cadena, 10, "2: %d\r\n", s2);
        Serial_Put_Bytes(port, BLOCKING, cadena, 9);
#endif
    }
}
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
