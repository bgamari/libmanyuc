/**************************************************************************//**
 * @defgroup SPI SPI Communication
 * @{
 * @brief    libmanyuc SPI Communication definitions
 * @date     May 2012
 * @author   Copyright (C) 2012 - Margarita Manterola Rivero
 *
 * @par
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * @par
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * @par
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA
 *
 ******************************************************************************/

#ifndef SPI_H
#define SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stdint.h>
#include "board.h"

    /** Opaque structure to hold SPI device
     *  The data contained in the structure depends on the
     *  architecture. It should be created through SPI_Init.
     */
    typedef struct _spi_t SPI_t;

    /** SPI Device modes: Master or Slave */
    typedef enum SPIMode {SPISlave, SPIMaster} SPIMode;
    /** SPI Data modes: clock polarity (high or low) and phase (rise or
     *  fall).*/ 
    typedef enum SPIDataMode {
        SPILowRise, SPILowFall, SPIHighFall, SPIHighRise
    } SPIDataMode;
    /** SPI Bit orders: LSB first or MSB first */
    typedef enum SPIBitOrder {
        SPIMSB, SPILSB,
    } SPIBitOrder;


    /** Creates the SPI device structure needed to communicate through SPI
     *  @param port The SPI port number to use, the ports available depend on
     *              the architecture.
     *  @param bit_order The order in which the bits are transmitted
     *                   (SPIMSB or SPILSB)
     *  @param data_mode The clock phase an polarity to use for
     *                   transmission.
     *  @param device_mode The SPI mode to use for this device 
                           (SPIMaster or SPISlave).
     *  @return A structure that represents an initialized SPI device.
     */
    SPI_t SPI_Init(uint8_t port, SPIBitOrder bit_order, 
        SPIDataMode data_mode, SPIMode device_mode);

    /** Reads and writes one byte through the SPI bus.
     *  @param device An initialized SPI device.
     *  @param data The byte to transmit to the bus.
     *  @return The byte read from the bus.
     */
    uint8_t SPI_Transmit_Byte(SPI_t device, uint8_t data);

    /** Transmits an arbitrary number of bytes through the SPI bus.
     *  @param device An initialized SPI device.
     *  @param data A pointer to an initialized byte array.
     *  @param length The amount of bytes to read/write into the array.
     *  @return The amount of bytes actually read/written.
     */
    unsigned int SPI_Transmit_Bytes(SPI_t device, uint8_t *data, 
        unsigned int length);

    /** Sets the bus frequency in hertz.
     *  @param device An initialized SPI device.
     *  @param hz The frequency to set in hertz.
     */
    void SPI_Frequency(SPI_t device, uint32_t hz);

//@}

#ifdef __cplusplus
}
#endif

#endif
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
