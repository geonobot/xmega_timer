/**
 * \file xmega_timer.c
 *
 * \date 26 nov. 2014
 * \author ldo
 *
 * \brief XMEGA timer library
 *
 * The TC has six different modes of operation :
 * Normal mode
 * Frequency Generation mode
 * Single Slope PWM
 * Dual Slope PWM, overflow on TOP
 * Dual Slope PWM, overflow on TOP and BOTTOM.
 * Dual Slope PWM, overflow on BOTTOM
 */

#include "xmega_timer.h"

ISR (TCC0_OVF_vect)
{

}

ISR (TCD0_OVF_vect)
{
  if (PORTA.IN == 0)
    {
      PORTA.OUT = 0xFF;
    }
  else
    {
      PORTA.OUT = 0x00;
    }
  TCD0.CNT = 0;
}

/**
 * In normal operation, the counter will count in the direction set by the direction (DIR) bit for each clock
 * until it reaches TOP or BOTTOM.
 * When up-counting, the counter counts from 0 to TOP (PER). When PER is reached, the counter is reset to zero.
 * When down-counting, the counter counts from BOTTOM to 0. When 0 is reached, the counter is set to BOTTOM.
 *
 * ATXMEGA128A1 use PORTC, PORTD, PORTE or PORTF. Each port has one Timer0 and one Timer1.
 * Notation TCC0, TCC1, TCD0, TCD1, TCE0, TCE1, TCF0 and TCF1
 *  */
void
xmega_timer_0_normal_mode_setup (volatile TC0_t * tc, uint16_t period,
				 TC_CLKSEL_t prescaler)
{
  /* set the PER[H:L] register to select the timer period */
  tc->PER = period; //PER is TOP;

  /* set the WGMODE[2:0] bits in CTRLB to select a normal mode */
  tc->CTRLB = TC_WGMODE_NORMAL_gc;

  /* set the OVFINTLVL[1:0] bits in INTCTRLA to enable timer overflow interrupt */
  tc->INTCTRLA = TC_OVFINTLVL_LO_gc;

  /* start the TC by selecting a clock source (CLKSEL[3:0] in CTRLA) */
  tc->CTRLA = prescaler;
  tc->CNT = 0;
}

/**
 * For frequency generation the period time (T) is controlled by the CCA register.
 * The waveform generation (WG) output is toggled on each compare match between the CNT and CCA registers
 */
void
xmega_timer_0_pwm_mode_setup (volatile TC0_t * tc, const uint8_t period,
			      TC_CLKSEL_t prescaler)
{
  /* set the PER[H:L] register to select the timer period */
  tc->PER = period;
  /* set the WGMODE[2:0] bits in CTRLB to select a waveform generation mode */
  tc->CTRLB = TC_WGMODE_SS_gc; /* single slope */

  /* start the TC by selecting a clock source (CLKSEL[3:0] in CTRLA) */
  tc->CTRLA = prescaler; //TC_CLKSEL_DIV8_gc;
}

/**
 *
 */
void
xmega_timer_0_pwm_enable (volatile TC0_t * tc, const uint8_t pin)
{
  /* set the CCAEN bit in CTRLB to enable Compare Channel A */
  tc->CTRLB |= (1 << (pin + TC0_CCAEN_bp));
}

/**
 *
 */
void
xmega_timer_0_pwm_duty_cycle (volatile TC0_t * tc, const uint8_t pin,
			      uint8_t duty_cycle)
{
  /* Write the new compare value to CCA[H:L] */
  switch (pin)
    {
    case 0:
      tc->CCA = duty_cycle;
      break;
    case 1:
      tc->CCB = duty_cycle;
      break;
    case 2:
      tc->CCC = duty_cycle;
      break;
    case 3:
      tc->CCD = duty_cycle;
      break;
    default:
      break;
    }

}
