/**
 ******************************************************************************
 * @file           : uart.h
 * @brief          : Header for uart.c file.
 *                   This file contains uart function definitions
 ******************************************************************************
 * @attention 
 *
 ******************************************************************************/

#ifndef UART_H_
#define UART_H_

/** Public Declarations */
void config_UART(void);
void uart_send(char * tx_buffer);

#endif /* UART_H_ */