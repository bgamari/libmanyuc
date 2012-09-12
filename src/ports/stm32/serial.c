/*
 * libmanyuc - STM32 serial communication file
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

#include "serial.h"
#include <stdlib.h>

#define UART_BLOCK_TIMEOUT      0xFFFFFFFF            // Timeout for blocking 

#define STM32_UART_SR_TXE    (1<<7)
#define STM32_UART_SR_RXNE   (1<<5)
#define STM32_UART_SR_IDLE   (1<<4)
#define STM32_UART_SR_ORE    (1<<3)
#define STM32_UART_SR_NF     (1<<2)
#define STM32_UART_SR_FE     (1<<1)
#define STM32_UART_SR_PE     (1<<0)

#define STM32_UART_CR1_UE    (1<<13)
#define STM32_UART_CR1_TE    (1<<3)
#define STM32_UART_CR1_RE    (1<<2)

const static USART_TypeDef *uart_regs[] = {
    USART1,
    USART2,
    USART3,
    UART4,
    UART5,
    USART6,
};

struct DMA_Channel_t {
    uint8_t dma_n;
    uint8_t stream_n;
    uint8_t channel;
};
    
struct {
    struct DMA_Channel_t rx, tx;
} uart_dma_info[] = {
    { // USART1
        .rx = { .dma_n=2, .stream_n=2, .channel=4 },
        .tx = { .dma_n=2, .stream_n=7, .channel=4 },
    },          
    { // USART2 
        .rx = { .dma_n=1, .stream_n=5, .channel=4 },
        .tx = { .dma_n=1, .stream_n=6, .channel=4 },
    },          
    { // USART3 
        .rx = { .dma_n=1, .stream_n=1, .channel=4 },
        .tx = { .dma_n=1, .stream_n=3, .channel=4 },
    },          
    { // USART4 
        .rx = { .dma_n=1, .stream_n=2, .channel=4 },
        .tx = { .dma_n=1, .stream_n=4, .channel=4 },
    },          
    { // USART5 
        .rx = { .dma_n=1, .stream_n=0, .channel=4 },
        .tx = { .dma_n=1, .stream_n=6, .channel=4 },
    },          
    { // USART6 
        .rx = { .dma_n=2, .stream_n=7, .channel=5 },
        .tx = { .dma_n=2, .stream_n=2, .channel=5 },
    },
};

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
    
DMA_Stream_TypeDef *get_dma_stream(uint8_t dma_n, uint8_t stream_n) {
    return dma_streams[8*(dma_n-1) + stream_n];
}

DMA_TypeDef *get_dma(uint8_t dma_n) {
    switch (dma_n) {
    case 1: return DMA1;
    case 2: return DMA2;
    default: return NULL;
    }
}

void dma_stream_clear_interrupts(uint8_t dma_n, uint8_t stream_n) {
    DMA_TypeDef *dma = get_dma(dma_n);
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

static uint8_t serial_initialized[] = { 0, 0, 0, 0 };

// Convert the serial port number to a serial port struct.
Serial_t Serial_Get(int number) {
    if (number < 0 || number > 5) number = 0;
    Serial_t port = {
        uart_regs[number],
        number,
    };
    return port;
}

extern uint32_t PeripheralClock;

// Create a serial port structure and initialize it
Serial_t Serial_Init(int number, int baudrate) {
    Serial_t port = Serial_Get(number);
    if (serial_initialized[number] != 0) {
        return port;
    }
    serial_initialized[number] = 1;

    // 1 - Start up clock to UART
    switch (number) {
    case 0:
      RCC->APB2ENR |= 1 << 4;
      break;
    case 1:
      RCC->APB1ENR |= 1 << 17;
      break;
    case 3:
      RCC->APB1ENR |= 1 << 18;
      break;
    case 4:
      RCC->APB1ENR |= 1 << 19;
      break;
    case 5:
      RCC->APB1ENR |= 1 << 20;
      break;
    case 6:
      RCC->APB2ENR |= 1 << 5;
    }

    // 2 - Set the baudrate
    port.uart->BRR = (1<<4) * PeripheralClock / 8 / 2 / baudrate;

    // 3 - Enable UART
    port.uart->CR1 |= STM32_UART_CR1_UE | STM32_UART_CR1_TE | STM32_UART_CR1_RE;

    return port;
}

// Returns if there is info available to be read
inline int Serial_Readable(Serial_t port) {
    return port.uart->SR & STM32_UART_SR_RXNE;
}

// Returns a byte read from the serial port. If there is no byte yet, it
// blocks until there is.
inline char Serial_Get_Byte(Serial_t port) {
    while (!Serial_Readable(port));
    return port.uart->DR;
}

// Reads the number of bytes from the serial port into the buffer.
// Memory for the buffer must have been allocated first.
uint32_t Serial_Get_Bytes(Serial_t port, SerialTransferMode mode,
                          char *data, uint32_t length) {
    uint32_t i = 0, wait;

    while (i < length) {

        // If non blocking, check if there's something to read
        // and if not, bail out.
        if (!(Serial_Readable(port)) && (mode == NONBLOCKING)) {
            break;
        }
        wait = UART_BLOCK_TIMEOUT;
        while (!(Serial_Readable(port)) && (mode == BLOCKING || (wait > 0))) {
            wait--;
        }
        if (!wait) break;

        data[i] = Serial_Get_Byte(port);
        i++;

    }
    return i;
}

// Returns if there is space to send a byte
inline int Serial_Sendable(Serial_t port) {
    return port.uart->SR & STM32_UART_SR_TXE;
}

// Sends a byte through the serial port. If there is no space, it blocks
// until there is.
inline void Serial_Put_Byte(Serial_t port, char data) {
    while (!Serial_Sendable(port));
    port.uart->DR = data;
}

// Send bytes in several different modes
uint32_t Serial_Put_Bytes(Serial_t port, SerialTransferMode mode,
                          char *data, uint32_t length)  {
    uint32_t i = 0;

    // Wait until previous transfer is complete
    //while (!(port.uart->SR & USART_SR_TC));
    //port.uart->SR = 0;

    if (mode == NONBLOCKING && length <= 0xffff) {
        uint8_t dma_n = uart_dma_info[port.number].tx.dma_n;
        uint8_t stream_n = uart_dma_info[port.number].tx.stream_n;
        DMA_Stream_TypeDef *stream = get_dma_stream(dma_n, stream_n);
        uint16_t channel = uart_dma_info[port.number].tx.channel;

        // Disable stream
        stream->CR &= ~DMA_SxCR_EN;
        while (stream->CR & DMA_SxCR_EN);

        NVIC_EnableIRQ(DMA2_Stream2_IRQn);
        NVIC_EnableIRQ(DMA2_Stream7_IRQn);
        dma_stream_clear_interrupts(dma_n, stream_n);

        port.uart->CR3 |= USART_CR3_DMAT;
        stream->CR = 0;
        stream->CR |= channel << 25;
        stream->CR |= 0x1 << 6; // Memory to Peripheral
        stream->CR |= DMA_SxCR_MINC;
        stream->CR |= DMA_SxCR_TCIE | DMA_SxCR_TEIE | DMA_SxCR_HTIE | DMA_SxCR_DMEIE;
        stream->FCR |= DMA_SxFCR_FEIE;
        stream->PAR = (uint32_t) &port.uart->DR;
        stream->M0AR = (uint32_t) data;
        stream->NDTR = length;
        port.uart->SR = 0;
        stream->CR |= DMA_SxCR_EN;
        return length;
    }

    // Disable DMA
    port.uart->CR3 &= ~USART_CR3_DMAT;

    while (i < length) {
        // If non-blocking, check for space and leave when none.
        if (!(Serial_Sendable(port)) && (mode == NONBLOCKING)) {
            break;
        }

        Serial_Put_Byte(port, data[i]);
        i++;
    }

    // Return the number of bytes that were sent
    return i;
}

FILE *Serial_Get_File(Serial_t port) {
    return NULL;
}

void DMA2_Stream2_IRQHandler() {
    dma_stream_clear_interrupts(2,2);
}
void DMA2_Stream7_IRQHandler() {
    dma_stream_clear_interrupts(2,7);
}

// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
