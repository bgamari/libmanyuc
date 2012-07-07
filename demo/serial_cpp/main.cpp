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
 This example demonstrates the different ways of sending strings
 through the serial port: blocking, non-blocking, background,
 using fprintf.

 Finally, the main loop repeats all the characters received from the
 serial port, through the serial port.  It also shows the lower half
 of the byte received using the leds.
*/

int main(void) {

    Bus leds(4, LED1, LED2, LED3, LED4);
    leds.mode(Output);
    leds.write_all(1);

    // Initialize serial port
    Serial port(0, 9600);

    // Send a string in non-blocking.  Only a part will be received
    uint32_t b = port.write("Hello World! How's it going? 0123456789ABCDEF\r\n", 47, NONBLOCKING);

    // Send a formatted string using fprintf
    fprintf(port, "\r\nSent bytes: %d\r\n", b);
    fprintf(port, "File pointer: %p\r\n", port.file());

    // Send a long string. Complete
    port.write("Hello World! How's it going? 0123456789ABCDEF\r\n", 47, BLOCKING);

    // Send strings in the background
    port.write("Yay! This is a very long string being sent on background.\r\n", 59, BACKGROUND);
    port.write("This is another long string being sent on background.\r\n", 55, BACKGROUND);
    port.write("This is yet another long string being sent on background.\r\n", 59, BACKGROUND);
    port.write("And this is yet another long string being sent on background.\r\n", 63, BACKGROUND);

    // Do something while the string is being sent
    uint32_t i;
    for (i = 0; i < 0xFFFFF; i++) {
        leds = (i >> 16);
    }

    // This string will only be sent once the others have been
    // completed.
    port.write("All strings sent, now echoing each key:\r\n", 41, BLOCKING);

    // Repeat the received byte
    while (1) {
        while (! port.readable());
        char c = port.getByte();
        leds = c;
        while (! port.sendable());
        port.putByte(c);
    }
}
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
