/**
 *******************************************************************************
 * @file           : uart.c
 * @brief          : Source file for UART Module
 *******************************************************************************
 * @attention
 *
 * @author          : Pedro Vilela (pvilela@inatel.br)
 *
 * All rights are reserved. Reproduction in whole or part is prohibited without
 * the written consent of the copyright owner.
 *******************************************************************************/

#include <msp430g2553.h>

/* UART header */
#include "uart.h"

#define SMCLK           1000000
#define BAUDRATE        9600

/**
 * @brief	Configures UART module.
 * @param	None	

 * @retval	None
 */
void uart_config(void)
{
  P1SEL = BIT1 + BIT2;
  P1SEL2 = BIT1 + BIT2;
  UCA0CTL1 |= UCSSEL_2;
  UCA0BR0 = (SMCLK/BAUDRATE)%256;
  UCA0BR1 = (SMCLK/BAUDRATE)/256;
  UCA0MCTL = UCBRS0;
  UCA0CTL1 &= ~UCSWRST; 
}

/**
 * @brief	Sends message through UART.
 * @param	[in] 	Pointer to buffer containing the message.

 * @retval	None
 */
void uart_send(char * tx_buffer)
{
  unsigned int i = 0;
  
  while(tx_buffer[i] != 0)
  {
    while((IFG2 & UCA0TXIFG) == 0);     
    UCA0TXBUF = tx_buffer[i];
    i++;
  }
}