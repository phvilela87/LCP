/**
 ******************************************************************************
 * @file           : adc.h
 * @brief          : Header for adc.c file.
 *                   This file contains adc function definitions
 ******************************************************************************
 * @attention 
 *
 ******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

/** Public Declarations */
void adc_init(void);
unsigned long read_sensor_one(void);
unsigned long read_sensor_two(void);

#endif /* ADC_H_ */