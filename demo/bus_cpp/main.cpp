/*
 * libmanyuc - Example of using the serial port
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

/*
 * This demo shows how to use a pin bus in C++.
 * First tt turns all leds on and off, 
 * then it shows a binary sequence through the leds.
 */
int main(void) {

    Bus leds(4, LED1, LED2, LED3, LED4);
    leds.mode(Output);

    leds.write_all(1);
    Delay(0.4);
    leds.write_all(0);
    Delay(0.4);
    leds.write_all(1);
    Delay(0.4);

    while (1) {
        // Do something while the string is being sent
        for (unsigned int i = 0; i < 0xFFFFF; i++) {
            leds = i;
            Delay_ms(50);
        }
    }
}
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
