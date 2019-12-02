/**
 *******************************************************************************
 * @file           : timer.c
 * @brief          : Source file for timer Module
 *******************************************************************************
 * @attention
 *
 * @author         : Pedro Vilela
 *
 * All rights are reserved. Reproduction in whole or part is prohibited without
 * the written consent of the copyright owner.
 *******************************************************************************/

/*********************************************************
    Includes.
*********************************************************/
#include <msp430g2553.h>

/* timer header */
#include "timer.h"
   
/*********************************************************
    Private definitions.
*********************************************************/
#define SMCLK           1000000UL
#define PWM_FREQUENCY   50

/*********************************************************
    Private variables.
*********************************************************/
int reference_time = 0;

 /*********************************************************
    Public functions.
*********************************************************/  
/**
 * @brief	Initialises timer peripheral.
 * @param	None	

 * @retval None
 */
void timer_init(void)
{
  TA0CCR0 = 24999;
  TA0CTL = (TASSEL_2 + MC_1 + ID_3);      // starts timer clock source as SMCLK/8 and UP mode
  TA0CCTL0 |= CCIE;                       // Enables interrupt for CCR0
  
  TA1CCTL1 |= OUTMOD_7;                   // CCR1 Reset/Set
  TA1CCR0 = (SMCLK/PWM_FREQUENCY)-1;      // PWM Period (20ms)
  TA1CCR1 = 0;                            // Duty cycle
  TA1CTL = (TASSEL_2 + ID_0 + MC_1);      // starts timer clock source as SMCLK and UP mode
}

/**
 * @brief	Retrieves timer ticks.
 * @param	None	

 * @retval None
 */
int timer_get_tick(void)
{
  return reference_time;
}

/**
 * @brief	Resets timer ticks.
 * @param	None	

 * @retval None
 */
void timer_reset_tick(void)
{
  reference_time = 0;
}

/* Timer A0 interrupt */
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0(void)
{
  reference_time++;
  TA0CCTL1 &= ~CCIFG;
}