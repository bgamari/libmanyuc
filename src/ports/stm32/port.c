/*
 * libmanyuc - STM32 initialization functions
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

#include "stm32f4xx.h"
#include "board.h"

#define CLOCK_SETUP           1
#define SCS_Val               0x00000020
#define CLKSRCSEL_Val         0x00000001
#define CCLKCFG_Val           0x00000003
#define USBCLKCFG_Val         0x00000000
#define PCLKSEL0_Val          0x00000000
#define PCLKSEL1_Val          0x00000000
#define PCONP_Val             0x042887DE
#define CLKOUTCFG_Val         0x00000000

#define HSE_CLK     (16000000UL)        /* External oscillator frequency      */
#define HSI_CLK     (HSI_VALUE )        /* Main oscillator frequency          */
#define RTC_CLK     (   32768UL)        /* RTC oscillator frequency           */
#define IRC_OSC     ( 4000000UL)        /* Internal RC oscillator frequency   */

/* F_cco0 = (2 * M * F_in) / N  */
#define __M               (((PLL0CFG_Val      ) & 0x7FFF) + 1)
#define __N               (((PLL0CFG_Val >> 16) & 0x00FF) + 1)
#define __FCCO(__F_IN)    ((2 * __M * __F_IN) / __N)
#define __CCLK_DIV        (((CCLKCFG_Val      ) & 0x00FF) + 1)

static const uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};


/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/

uint32_t SystemCoreClock; /* System Clock Frequency (Core Clock)*/
uint32_t PeripheralClock; /* Peripheral Clock value */

void SystemCoreClockUpdate(void) {           /* Get Core Clock Frequency      */
    uint32_t tmp = 0, pllvco = 0, pllp = 2, pllsource = 0, pllm = 2;

    tmp = RCC->CFGR & RCC_CFGR_SWS;
    switch (tmp)
    {
    case 0x00: // HSI in use
        SystemCoreClock = HSI_VALUE;
        break;

    case 0x04: // HSE in use
        SystemCoreClock = HSE_VALUE;
        break;

    case 0x08: // PLL in use
        /* PLL_VCO = (HSE_VALUE or HSI_VALUE / PLL_M) * PLL_N
           SYSCLK = PLL_VCO / PLL_P
        */    
        pllsource = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) >> 22;
        pllm = RCC->PLLCFGR & RCC_PLLCFGR_PLLM;
      
        if (pllsource != 0)
            {
                /* HSE used as PLL clock source */
                pllvco = (HSE_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
            }
        else
            {
                /* HSI used as PLL clock source */
                pllvco = (HSI_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);      
            }

        pllp = (((RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >>16) + 1 ) *2;
        SystemCoreClock = pllvco/pllp;
        break;

    default:
        SystemCoreClock = HSI_VALUE;
        break;
    }

    tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> 4)];
    SystemCoreClock >>= tmp;
}


// Used for initializing global variables
extern unsigned int _start_data;
extern unsigned int _end_data;
extern unsigned int _start_datai;
extern unsigned int _end_datai;

void init(void) {
    // Reset clock configuration
    RCC->CR |= 0x1;
    RCC->CFGR = 0x0;
    RCC->CR &= 0xfef6ffff;
    RCC->PLLCFGR = 0x24003010;
    RCC->CR &= 0xfffbffff;
    RCC->CIR = 0x0;

    // Enable things that don't fit elsewhere
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN | RCC_AHB1ENR_DMA2EN;

    // Update the SystemCoreClock value
    SystemCoreClockUpdate();

    // Store PeripheralClock value
    PeripheralClock = SystemCoreClock;
    if ((RCC->CFGR >> 7) & 0x1) {
        PeripheralClock >>= (RCC->CFGR >> 4) & 0x3;
    }

    if (SysTick_Config(SystemCoreClock / 1000)) {   /* Setup SysTick Timer for 1 msec interrupts  */
        while (1);              /* Capture error */
    }

    __enable_irq();

    // Initialize Global Variables
    uint32_t *data_begin  = (uint32_t *) &_start_data;
    uint32_t *data_end    = (uint32_t *) &_end_data;
    uint32_t *datai_begin = (uint32_t *) &_start_datai;
    uint32_t *datai_end   = (uint32_t *) &_end_datai;
    while (data_begin < data_end) {
        *data_begin = *datai_begin;
        data_begin++;
        datai_begin++;
    }

    /* C++ static constructors */
    extern void (*__init_array_start []) (void) __attribute__((weak)); 
    extern void (*__init_array_end []) (void) __attribute__((weak)); 
    int count = __init_array_end - __init_array_start, i; 
    for (i = 0; i < count; i++) __init_array_start[i]();

}

// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4: