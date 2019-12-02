/**
 *******************************************************************************
 * @file           : adc.c
 * @brief          : Source file for ADC Module
 *******************************************************************************
 * @attention
 *
 * @author        : Pedro Vilela
 *
 * All rights are reserved. Reproduction in whole or part is prohibited without
 * the written consent of the copyright owner.
 *******************************************************************************/

/*********************************************************
    Includes.
*********************************************************/
#include <msp430g2553.h>

/* ADC header */
#include "adc.h"

/*********************************************************
    Public functions.
*********************************************************/
/**
 * @brief	Initialises ADC peripheral.
 * @param	None	

 * @retval None
 */
void adc_init(void)
{
  ADC10AE0 = BIT6 + BIT7;                    // Sets P1.6 and P1.7 pins as ADC input
  ADC10CTL1 = ADC10SSEL_3;                   // SMCLK
  ADC10CTL0 |= SREF_0;                       // Vcc & Vss as reference
}

/**
 * @brief	Reads value from LDR sensor one.
 * @param	None	

 * @retval	[out]   ADC level(0-1023) read from P1.6
 */
unsigned long read_sensor_one(void)
{
  ADC10CTL0 &= ~ADC10ON;                      // Disables ADC
  ADC10CTL0 &= ~(ENC + ADC10SC);              // Stops sampling and conversion process
  ADC10CTL1 = INCH_6;                         // Sets channel 6
  ADC10CTL0 = ADC10ON;                        // Enables ADC
  ADC10CTL0 |= (ENC + ADC10SC);               // Starts ampling and conversion process
  
  return ADC10MEM;                            // Returns the value held in ADC10MEM 
}

/**
 * @brief	Reads value from LDR sensor two.
 * @param	None	

 * @retval	[out]   ADC level(0-1023) read from P1.6
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