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
   
/**
 * @brief	Initialises timer module.
 * @param	None	

 * @retval	None
 */
void timer_init(void)
{
  TA1CCTL1 |= OUTMOD_7; 
  TA1CCR0 = (SMCLK/PWM_FREQUENCY)-1;
  TA1CCR1 = 0;
  TA1CTL = (TASSEL_2 + ID_0 + MC_1);
}