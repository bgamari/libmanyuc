/*
 * libmanyuc - Template Arch Timers
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

#include "timers.h"

// Create a scheduler
Scheduler_t Scheduler_Init_us(Int_Func func, unsigned int time_delay,
                              uint8_t repeat) {

    Scheduler_t scheduler;
    return scheduler;
}

void TIMER0_IRQHandler() {
    // For counting - not used for timers
}

void TIMER1_IRQHandler() {
}

void TIMER2_IRQHandler() {
}

void TIMER3_IRQHandler() {
}

// SysTick Handler
volatile uint32_t msTicks;      /* counts 1ms timeTicks */
void SysTick_Handler(void) {
    msTicks++;
}

// Delay in miliseconds
void Delay_ms(unsigned int ms) {
    uint32_t curTicks;
    curTicks = msTicks;
    while ((msTicks - curTicks) < ms);
}

// Delays in microseconds.
void Delay_us(unsigned int us) {
    // TODO
}


// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
