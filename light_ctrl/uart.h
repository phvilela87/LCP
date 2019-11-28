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

/*********************************************************
    Public functions.
*********************************************************/
void uart_config(void);
void uart_send(char * tx_buffer);

#endif /* UART_H_ */