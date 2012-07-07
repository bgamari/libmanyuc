/*
 * libmanyuc - LPC io file
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

/* Convert the pin name to a pin struct. */
Pin_t Pin_Get(PinName pin_name) {
    uint32_t address = pin_name - LPC_GPIO_BASE;
    Pin_t pin = { address / 32, address % 32, 1 << (address % 32) };
    return pin;
}

// Set pin input mode
void Pin_Mode(Pin_t pin, PinMode mode) {
// TODO: lock for concurrency
    uint32_t port = _get_half_port(pin);
    uint32_t shift = _get_half_mask(pin);

    if (mode == Output) {
        Pin_Output(pin);
    } else if (mode == Input) {
        Pin_Input(pin);
    } else if (mode < 4) {
        // Set input type (PullUp, PullDown, PullNone)
        LPC_PINCON->PINMODE[port] &= ~(3 << shift);
        LPC_PINCON->PINMODE[port] |= (mode << shift);
    } else if (mode == OpenDrain) {
        // Set opendrain
        _set_open_drain(pin.port, pin.mask);
    } else if (mode == NormalMode) {
        _set_normal_mode(pin.port, pin.mask);
    } else {
        // Set pin primary / secondary / etc function.
        mode -= 8;
        LPC_PINCON->PINSEL[port] &= ~(3 << shift);
        LPC_PINCON->PINSEL[port] |= (mode << shift);
    }
}

#include <stdarg.h>
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

void PinBus_Mode(PinBus_t bus, PinMode mode) {

    if (mode == Output) {
        PinBus_Output(bus);
    } else if (mode == Input) {
        PinBus_Input(bus);
    } else if (mode == OpenDrain) {
        return _PinBus_Apply(bus, _set_open_drain);
    } else if (mode == NormalMode) {
        return _PinBus_Apply(bus, _set_normal_mode);
    }

    int i;
    // Create a 32bit mask that repeats the mode 16 times
    uint32_t mode_mask = mode & 0x3;
    for (i = 2; i < 32; i *= 2) {
        mode_mask = (mode_mask << i) + mode_mask;
    }

    int port;
    for (port = 0; port < MAX_PORTS; port++) {
        for (i = 0; i < 2; i++) {

            uint32_t pin_mask = bus.ports[port].half_mask[i];
            if (!pin_mask) continue;

            uint32_t value = pin_mask & mode_mask;
            uint8_t half_port = 2 * port + i;
            if (mode < 4) {
                LPC_PINCON->PINMODE[half_port] &= ~(pin_mask);
                LPC_PINCON->PINMODE[half_port] |= value;
            } else {
                LPC_PINCON->PINSEL[half_port] &= ~(pin_mask);
                LPC_PINCON->PINSEL[half_port] |= value;
            }
        }
    }
}

// Returns this arch's leds.
PinBus_t PinBus_Get_Notification() {
    return PinBus_Get(4, LED1, LED2, LED3, LED4);
}

// Interrupt handling

#include "hash.h"

// Interrupt table where all interrupts are registered
Hash_t *io_interrupt_table = NULL;

#define _IO_PORT_SHIFT 32
#define _IO_MODE_SHIFT 64

// Returns the corresponding byte identification for the pin
// address, port, and interrupt mode
static inline uint8_t io_interrupt_get_byte(uint32_t address,
uint8_t port, uint8_t mode) {
    uint8_t pos = address;
    pos += _IO_PORT_SHIFT * (port / 2);
    pos += _IO_MODE_SHIFT * (mode);
    return pos;
}

// Call both handlers (if apropriate) and clear the interrupts
static inline void io_interrupt_call_handlers(uint32_t *states,
uint8_t id, uint8_t port_shift) {

    uint32_t mask = (1 << id);
    Int_Func f = NULL;

    // Check which (or both) of the handlers has to be called
    if (states[0] & mask) {
        f = (Int_Func) Hash_Get(io_interrupt_table, id
        + port_shift);
        if (f != NULL) f();
    }
    if (states[1] & mask) {
        f = (Int_Func) Hash_Get(io_interrupt_table, id +
        port_shift + _IO_MODE_SHIFT);
        if (f != NULL) f();
    }
    // Set the interrupt as handled
    states[2] |= mask;
}

// Iterate over a register of interrupts, calling the functions
static void io_interrupt_read_all(uint32_t *states,  uint8_t port_shift) {

    // OR both states (postive edge and negative edge)
    uint32_t ints = states[0] | states[1];

    // Iterate the interrupt state vector until all interrupts
    // have been handled
    uint8_t j = 0;
    while (ints != 0) {
        if (ints & 0x1) {
            io_interrupt_call_handlers(states, j, port_shift);
        }
        ints >>= 1;
        j++;
    }
}

void EINT3_IRQHandler(void) {

    if (io_interrupt_table == NULL) return;

    io_interrupt_read_all((uint32_t *) LPC_GPIOINT->IO0IntStat, 0);
    io_interrupt_read_all((uint32_t *) LPC_GPIOINT->IO2IntStat, _IO_PORT_SHIFT);
}

// Initializes the interrupt table
static void io_interrupt_init() {
    io_interrupt_table = Hash_Init(NULL);
    NVIC->ISER[0] |= (1 << EINT3_IRQn);
}

void Pin_Int_Enable(struct _pin_t pin, IOIntMode mode) {
    // Enable the interrupt in the microcontroller
    if (pin.port == 0) {
        LPC_GPIOINT->IO0IntEn[mode] |= pin.mask;
    } else {
        LPC_GPIOINT->IO2IntEn[mode] |= pin.mask;
    }
}

void Pin_Int_Disable(struct _pin_t pin, IOIntMode mode) {
    // Disable the interrupt in the microcontroller
    if (pin.port == 0) {
        LPC_GPIOINT->IO0IntEn[mode] &= ~(pin.mask);
    } else {
        LPC_GPIOINT->IO2IntEn[mode] &= ~(pin.mask);
    }
}

void Pin_Int_Attach(struct _pin_t pin, void(*function)(void), IOIntMode mode) {

    // Only allow ports 0 and 2 in the LPC arch.
    if ((pin.port != 0) && (pin.port != 2)) return;

    // Initialize the table if necessary
    if (io_interrupt_table == NULL) {
        io_interrupt_init();
    }

    // Get the byte for the hash
    uint8_t pos = io_interrupt_get_byte(pin.address, pin.port, mode);
    // Store the function pointer
    Hash_Set(io_interrupt_table, pos, (void *) function);

    Pin_Int_Enable(pin, mode);
}

// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
