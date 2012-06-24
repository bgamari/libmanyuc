/*
 * libmanyuc - LPC SPI specifications file
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

#ifndef LPC17XX_SPI_PORT_H
#define LPC17XX_SPI_PORT_H

#ifdef __cplusplus
extern "C" {
#endif

	#include "common.h"

	typedef enum SPIPinNames {
		SCLK = ARM_P0_15,
		SSEL = ARP_P0_16,
		MISO = ARP_P0_17,
		MOSI = ARP_P0_18,
	} SPIPinNames;

    struct _spi_t {
        uint8_t port;
        uint8_t mode;
    };

#ifdef __cplusplus
}
#endif
