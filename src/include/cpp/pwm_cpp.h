/*
 * libmanyuc - pwmpin cpp header file
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

#ifndef PWM_CPP_H
#define PWM_CPP_H

#include "io.h"
#include "pwm.h"
#include <stdint.h>

/** The PWMPin class represents a pin on the board,
 *  that can be used to generate Pulse Width Modulation signals.
 *
 *  @author Margarita Manterola
 *  @date 2012
 */

class PWMPin {
private:
    PWMPin_t pin;
public:
    /** PWMPin Constructor.
     *  Initializes the pin for Pulse Width Modulation and starts creating
     *  a pulse, with the default duty cycle.
     *  @param pin_name the board name for the pin.
     */
    PWMPin(PinName pin_name) {
        this->pin = PWMPin_Init(pin_name);
    }

    /** Sets the period of the PWM signal.
     *  @param s The period of the signal, in seconds.
     */
    void set_period_s(float s) {
        PWMPin_Set_Period_s(this->pin, s);
    }

    /** Sets the period of the PWM signal.
     *  @param ms The period of the signal, in milliseconds.
     */
    void set_period_ms(float ms) {
        PWMPin_Set_Period_ms(this->pin, ms);
    }

    /** Sets the period of the PWM signal.
     *  @param us The period of the signal, in microseconds.
     */
    void set_period_us(float us) {
        PWMPin_Set_Period_us(this->pin, us);
    }

    /** Sets the duty cycle of the PWM signal.
     *  @param duty The duty cycle to set. Values should be between 0 and 1.
     *  0 means always off, 1 means always on.
     */
    void set_duty_cycle(float duty) {
        PWMPin_Set_Duty_Cycle(this->pin, duty);
    }

    /** Sets the exact cycle count, the meaning of this value is
     *  architecture dependant.
     *  @param count The amount of cycles that the signal should be on.
     */
    void set_cycle_count(unsigned int count) {
        PWMPin_Set_Cycle_Count(this->pin, count);
    }

    /** Returns the currently set duty cycle.
     *  @return The currently set duty cycle for the pin.
     */
    float get_duty_cycle() {
        return PWMPin_Get_Duty_Cycle(this->pin);
    }

    // Operator overloading

    /** Shorthand for set_duty_cycle, 
     *  sets the duty cycle for the pin. */
    PWMPin &operator= (float value) {
        this->set_duty_cycle(value);
        return *this;
    }

    /** Shorthand for get_duty_cycle, returns the current 
     *  duty cycle of the pin. */
    operator float() {
        return this->get_duty_cycle();
    }
};

#endif
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
