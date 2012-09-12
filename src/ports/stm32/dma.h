/*
 * libmanyuc - STM32 DMA file
 * Copyright (C) 2012 - Ben Gamari
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

#ifndef STM32_DMA_H
#define STM32_DMA_H

#include <stdint.h>
#include "common.h"

struct DMA_Channel_t {
    uint8_t dma_n;
    uint8_t stream_n;
    uint8_t channel;
};

DMA_Stream_TypeDef *DMA_Get_Stream_Regs(uint8_t dma_n, uint8_t stream_n);

DMA_TypeDef *DMA_Get_Regs(uint8_t dma_n);

void DMA_Clear_Stream_Interrupts(uint8_t dma_n, uint8_t stream_n);

#endif
