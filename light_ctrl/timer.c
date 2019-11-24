/**
 *******************************************************************************
 * @file           : timer.c
 * @brief          : Source file for timer Module
 *******************************************************************************
 * @attention
 *
 * @author          : Pedro Vilela (pvilela@inatel.br)
 *
 * All rights are reserved. Reproduction in whole or part is prohibited without
 * the written consent of the copyright owner.
 *******************************************************************************/

#include <msp430g2553.h>

/* timer header */
#include "timer.h"
   
#define SMCLK           1000000UL
#define PWM_FREQUENCY   50

int reference_time = 0;
   
/**
 * @brief	Initialises timer module.
 * @param	None	

 * @retval	None
 */
void timer_init(void)
{
  TA0CCR0 = 24999;
  TA0CTL=TASSEL_2 + MC_1 + ID_3;
  TA0CCTL0|=CCIE;
  
  TA1CCTL1 |= OUTMOD_7; 
  TA1CCR0 = (SMCLK/PWM_FREQUENCY)-1;
  TA1CCR1 = 0;
  TA1CTL = (TASSEL_2 + ID_0 + MC_1);
}

/**
 * @brief	Gets time ticks.
 * @param	None	

 * @retval	[out]
 */
int timer_get_tick(void)
{
  return reference_time;
}

/**
 * @brief	Gets time ticks.
 * @param	None	

 * @retval	None
 */
void timer_reset_tick(void)
{
  reference_time = 0;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0(void)
{
  reference_time++;
  TA0CCTL1 &= ~CCIFG;
}