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

#include "dma.h"
#include <stdlib.h>

static DMA_Stream_TypeDef *dma_streams[] = {
    DMA1_Stream0,
    DMA1_Stream1,
    DMA1_Stream2,
    DMA1_Stream3,
    DMA1_Stream4,
    DMA1_Stream5,
    DMA1_Stream6,
    DMA1_Stream7,

    DMA2_Stream0,
    DMA2_Stream1,
    DMA2_Stream2,
    DMA2_Stream3,
    DMA2_Stream4,
    DMA2_Stream5,
    DMA2_Stream6,
    DMA2_Stream7,
};
    
DMA_Stream_TypeDef *DMA_Get_Stream_Regs(uint8_t dma_n, uint8_t stream_n) {
    return dma_streams[8*(dma_n-1) + stream_n];
}

DMA_TypeDef *DMA_Get_Regs(uint8_t dma_n) {
    switch (dma_n) {
    case 1: return DMA1;
    case 2: return DMA2;
    default: return NULL;
    }
}

void DMA_Clear_Stream_Interrupts(uint8_t dma_n, uint8_t stream_n) {
    DMA_TypeDef *dma = DMA_Get_Regs(dma_n);
    __IO uint32_t *reg;

    if (stream_n < 4) {
        reg = &dma->LIFCR;
    } else {
        reg = &dma->HIFCR;
        stream_n -= 4;
    }

    switch (stream_n) {
    case 0: *reg = 0x3d << 0; break;
    case 1: *reg = 0x3d << 6; break;
    case 2: *reg = 0x3d << 16; break;
    case 3: *reg = 0x3d << 22; break;
    }
}

