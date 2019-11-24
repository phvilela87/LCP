/**
 *******************************************************************************
 * @file           : adc.c
 * @brief          : Source file for ADC Module
 *******************************************************************************
 * @attention
 *
 * @author          : Pedro Vilela (pvilela@inatel.br)
 *
 * All rights are reserved. Reproduction in whole or part is prohibited without
 * the written consent of the copyright owner.
 *******************************************************************************/

#include <msp430g2553.h>

/* ADC header */
#include "adc.h"

/**
 * @brief	Initialises the ADC module.
 * @param	None	

 * @retval	None
 */
void adc_init(void)
{
  ADC10AE0 = BIT6 + BIT7;
  ADC10CTL1 = ADC10SSEL_3;
  ADC10CTL0 |= SREF_0;
}

/**
 * @brief	Reads value from LDR sensor one.
 * @param	None	

 * @retval	[out] 
 */
unsigned long read_sensor_one(void)
{
  ADC10CTL0 &= ~ADC10ON;
  ADC10CTL0 &= ~(ENC + ADC10SC);
  ADC10CTL1 = INCH_6;
  ADC10CTL0 = ADC10ON;
  ADC10CTL0 |= (ENC + ADC10SC);
  
  return ADC10MEM;
}

/**
 * @brief	Reads value from LDR sensor two.
 * @param	None	

 * @retval	[out] 
 */
unsigned long read_sensor_two(void)
{
  ADC10CTL0 &= ~ADC10ON;
  ADC10CTL0 &= ~(ENC + ADC10SC);
  ADC10CTL1 = INCH_7;
  ADC10CTL0 = ADC10ON;
  ADC10CTL0 |= (ENC + ADC10SC);
     
  return ADC10MEM;
}