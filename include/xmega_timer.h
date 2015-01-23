/*
 * timer.h
 *
 *  Created on: 26 nov. 2014
 *      Author: ldo
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
#include <avr/interrupt.h>

/**
 * \fn void xmega_timer_0_normal_mode_setup (volatile TC0_t * tc, uint16_t period, TC_CLKSEL_t prescaler)
 * \brief setup timer tc in normal mode
 * \param tc : timer to setup
 * \param user_function
 * \param period
 * \param prescaler
 */
void
xmega_timer_0_normal_mode_setup (volatile TC0_t * tc, uint16_t period,
				 TC_CLKSEL_t prescaler);

/**
 * \fn void xmega_timer_0_pwm_mode_setup (volatile TC0_t * tc, const uint8_t period, TC_CLKSEL_t prescaler)
 * \brief
 * \param tc
 * \param period
 * \param prescaler
 */
void
xmega_timer_0_pwm_mode_setup (volatile TC0_t * tc, const uint8_t period,
			      TC_CLKSEL_t prescaler);

/**
 * \fn void xmega_timer_0_pwm_enable (volatile TC0_t * tc, const uint8_t pin)
 * \brief enable pwm tc pin
 * \param tc timer0
 * \param pin from 0 to 3
 */
void
xmega_timer_0_pwm_enable (volatile TC0_t * tc, const uint8_t pin);

/**
 * \fn void xmega_timer_0_pwm_duty_cycle (volatile TC0_t * tc, const uint8_t pin, uint8_t duty_cycle)
 * \brief write duty cycle
 * \param tc timer0
 * \param pin from 0 to 3
 */
void
xmega_timer_0_pwm_duty_cycle (volatile TC0_t * tc, const uint8_t pin,
			      uint8_t duty_cycle);

#endif /* TIMER_H_ */
