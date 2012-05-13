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

uint32_t i;
Bus_t leds;

// Interrupt handler: increments the counter and shows the number
// divided by (256*256).
void count(void) {
	i++;
	Bus_Write(leds, (i>>16));
}

/* This example counts the number of interrupts received on pin 10,
 * which is toggled by the program in an infinite loop, showing a
 * number in binary using the leds. */
int main(void) {

	// Creates a bus with the 4 leds
	leds = Bus_Get (4, LED4, LED3, LED2, LED1);
	Pin_t in = Pin_Get(P10);

	Bus_Output(leds);
	Pin_Output(in);

	Pin_Int_Attach(in, count, IOIntFall);

	int i = 0;
	// Show a binary combination of leds
    while(1) {
		Pin_On(in);
		Pin_Off(in);
    }
}
