/*
 * libmanyuc - STM32 PWM File
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

#include "pwm.h"
#include "io.h"

// external variable set on port.c
extern uint32_t PeripheralClock;

// static variable to know if the pwm was initialized or not
static uint8_t _pwm_initialized = 0;

// General initialization function, to be run only once.
inline void pwm_init() {

    _pwm_initialized = 1;
}


PWMPin_t PWMPin_Get(PinName pin_name) {

}

// Set period functions
void PWMPin_Set_Period_s(PWMPin_t pin, float s) {
}
void PWMPin_Set_Period_ms(PWMPin_t pin, float ms) {
}
void PWMPin_Set_Period_us(PWMPin_t pin, float us) {
}

// Set duty cycle functions
void PWMPin_Set_Duty_Cycle(PWMPin_t pin, float duty) {
}

void inline PWMPin_Set_Cycle_Count(PWMPin_t pin, unsigned int count) {
}

float PWMPin_Get_Duty_Cycle(PWMPin_t pin) {
}

// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
