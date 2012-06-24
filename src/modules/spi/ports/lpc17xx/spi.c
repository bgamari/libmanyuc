/*
 * libmanyuc - LPC SPI File
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

#include "spi.h"
#include "spi_port.h"
#include "io.h"

// SPI transmission Flag 
#define SPI_SPSR_SPIF       ((1<<7))

// Transmission modes
#define SPI_SPCR_MSTR(n)    ((((0x1 & n)<<5))
#define SPI_SPCR_LSBF(n)    ((((0x1 & n)<<6))
#define SPI_SPCR_CPCH(n)    ((((0x3 & n)<<3))

// Data
#define SPI_SPDR_LO_MASK    ((0xFF))

// Power
#define SPI_POWER_BITMASK   ((1 << 8))

// external variable set on port.c
extern uint32_t PeripheralClock;

// Set the clock frequency
static inline void _set_clock(uint8_t port, uint32_t hz) {
    uint8_t value = (0xFF & (PeripheralClock / hz));
    if (value % 2) value -= 1;
    if (value < 8) value = 8;
    LPC_SPI->SPCCR = value;
}

SPI_t SPI_Init(uint8_t port, SPIBitOrder bit_order,
        SPIDataMode data_mode, SPIMode device_mode) {
    if (port > r01) Show_Error();

    // Get involved pins
    Pin_t sclk = Pin_Get((PinName) SCLK);
    Pin_t miso = Pin_Get((PinName) MISO);
    Pin_t mosi = Pin_Get((PinName) MOSI);

    // Set function
    Pin_Mode(sclk, Alt3);
    Pin_Mode(miso, Alt3);
    Pin_Mode(mosi, Alt3);

    if (device_mode == SPISlave) {
        // If slave, set the mode for slave select
        Pin_t ssel = Pin_Get((PinName) SSEL);
        Pin_Mode(ssel, Alt3);
    } else {
        // If master, set default clock.
        LPC_SPI->SPCCR = 8;
    }

    // Turn SPI on
    LPC_SC->PCONP |= SPI_POWER_BITMASK;
    // Set modes
    LPC_SPI->SPCR = SPI_SPCR_MSTR(device_mode) | 
        SPI_SPCR_LSBF(bit_order) | SPI_SPCR_CPCH(data_mode);

    // Return the SPI device
    SPI_t device = { port, device_mode };
    return device;
}

inline uint8_t SPI_Transmit_Byte(SPI_t device, uint8_t data)
{
    // Send byte
    LPC_SPI->SPDR = data;
    // Wait for end of transmission
    while (!(LPC_SPI->SPCR & SPI_SPSR_SPIF));
    // Return received byte
    return (SPI_SPDR_LO_MASK & LPC_SPI->SPDR); 
}

unsigned int SPI_Transmit_Bytes(SPI_t device, uint8_t *data,
        unsigned int length);

    unsigned int i = 0;
    for (; i < length; i++) {
        data[i] = SPI_Transmit_Byte(device, data[i]);
    }
    return i;
}

void SPI_Frequency(SPI_t device, uint32_t hz) {
    _set_clock(device.port, hz);
}

// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
