/*
 * libmanyuc - pinbus cpp file
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

#include "bus_cpp.h"
#include <stdarg.h>
#include <stdlib.h>

// Only the constructor is here, the rest are all inline functions.

Bus::Bus(int npins, ...) {

    this->copy = false;

    // Get the pinBus
    va_list pins;
    va_start(pins, npins);
    this->bus.pinBus = vPinBus_Get(npins, pins);
    this->bus.npins = npins;
    va_end(pins);

    // Get all the pins
    va_start(pins, npins);
    this->bus.pins = (Pin_t*) malloc(sizeof(Pin_t) * npins);
    int i;
    for (i = 0; i < npins; i++) {
        this->bus.pins[i] = Pin_Get((PinName) va_arg(pins, uint32_t));
    }
    va_end(pins);

}

Bus& Bus::operator= (const Bus &source)
{
    // check for self-assignment by comparing the address of the
    // implicit object and the parameter
    if (this == &source)
        return *this;
 
    // do the copy
    this->bus = source.bus;
    this->copy = true;
 
    // return the existing object
    return *this;
}


// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
