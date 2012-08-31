/*
 * libmanyuc - STM32 IO file
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

#include "io.h"
#include <stdarg.h>

// Convert the pin name to a pin struct.
Pin_t Pin_Get(PinName pin_name) {
    uint32_t address = pin_name;
    Pin_t pin = { address / 16, address % 16, 1 << (address % 16) };
    // Enable clock to GPIO port
    RCC->AHB1ENR |= 1 << pin.port; 
    return pin;
}

// Set pin input/output mode
void Pin_Mode(Pin_t pin, PinMode mode) {
    uint32_t shift = 2 * pin.address;
    uint32_t shift4 = 4 * pin.address;
    
    if (mode == Output) {
        GPIOR[pin.port].MODER &= ~(3 << shift);
        GPIOR[pin.port].MODER |= 1 << shift;
    } else if (mode == Input) {
        GPIOR[pin.port].MODER &= ~(3 << shift);
    } else if (mode < 4) {
        // Set input type (PullUp, PullDown, PullNone)
        GPIOR[pin.port].PUPDR &= ~(3 << shift);
        GPIOR[pin.port].PUPDR |= mode << shift;
    } else if (mode == OpenDrain) {
        GPIOR[pin.port].OTYPER |= 1 << pin.address;
    } else if (mode == NormalMode) {
        GPIOR[pin.port].OTYPER |= 1 << pin.address;
    } else if (mode == Analog) {
        GPIOR[pin.port].MODER |= 3 << shift;
    } else if (mode >= Alt0) {
        mode -= Alt0;
        if (pin.port < 8) {
            GPIOR[pin.port].AFRL &= ~(0xf << shift4);
            GPIOR[pin.port].AFRL |= (mode << shift4);
        } else {
            GPIOR[pin.port].AFRH &= ~(0xf << shift4);
            GPIOR[pin.port].AFRH |= (mode << shift4);
        }
        GPIOR[pin.port].MODER &= ~(3 << shift);
        GPIOR[pin.port].MODER |= 2 << shift;
    }
}

// Construct a pin bus
PinBus_t vPinBus_Get(int npins, va_list pins) {
    int i;
    PinBus_t bus = { { {0, {0, 0}}, {0, {0, 0}}, {0, {0, 0}}, } };

    for (i = 0; i < npins; i++) {
        uint32_t address = va_arg(pins, uint32_t) - LPC_GPIO_BASE;
        uint8_t number = address % 32;
        // Add the pin to the 32 pin mask
        bus.ports[address / 32].mask |= 1 << number;
        // And the pin to the 16 pin mask with 2 bits per pin.
        if (number < 16) {
            bus.ports[address / 32].half_mask[0] |= 3 << (number * 2);
        } else {
            bus.ports[address / 32].half_mask[1] |= 3 << ((number - 16) * 2);
        }
    }
    return bus;
}

// Set PinBus input/output mode
void PinBus_Mode(PinBus_t bus, PinMode mode) {
}

// Returns this arch's leds.
PinBus_t PinBus_Get_Notification() {
    return PinBus_Get(0);
}

// Interrupt handling


// Enable interrupts on this pin
void Pin_Int_Enable(struct _pin_t pin, IOIntMode mode) {
    // TODO
}

// Disable interrupts on this pin
void Pin_Int_Disable(struct _pin_t pin, IOIntMode mode) {
    // TODO
}

// Attach a function to a pin interrupt. Once this is done, enable the
// interrupt.
void Pin_Int_Attach(struct _pin_t pin, void(*function)(void), IOIntMode mode) {
    // TODO
}


// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
