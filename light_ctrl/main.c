/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
 *******************************************************************************/

#include <msp430g2553.h>

/* standard library header */
#include "stdio.h"

/* UART header */
#include "uart.h"

/* ADC header */
#include "adc.h"

/* timer header */
#include "timer.h"

#define TX_BUFFER_SIZE          64
#define SERVO_STEP_0            540
#define SERVO_STEP_10           736
#define SERVO_STEP_50           1520
#define SERVO_STEP_100          2500   

unsigned char led[3] = { 0 };
unsigned char window = 0;
unsigned char active = 0;
unsigned long luminosity_sensor1 = 0;
unsigned long luminosity_sensor2 = 0;
unsigned long luminosity_average = 0;

char tx_buffer[TX_BUFFER_SIZE] = { 0 };

void check_system(void);
void leds_off(void);
void send_message(void);

void init_hw(void)
{ 
  P2OUT &= 0x00;                                        // Shut down everything
  P2DIR = (BIT2 + BIT3 + BIT4 + BIT5);                 // Set P2.3, P2.4, and P2.5 pins as output        
  P2SEL |= BIT2;
  
  P1OUT &= 0x00;
  P1DIR &= 0x00;
  P1REN |= BIT4;                       
  P1OUT |= BIT4;
}

void config_interrupt(void)
{
  P1IE |= BIT4;                         // P1.4 interrupt enabled
  P1IES |= BIT4;                        // P1.4 Hi/lo edge
  P1IFG &= ~BIT4;                       // P1.4 IFG cleared
  
  P1REN |= BIT4;                        // Enable internal pull-up/down resistors
  P1OUT |= BIT4;                        // Select pull-up mode for P1.4
  
  _BIS_SR(GIE);                         // Enable global interrupt
}

void leds_off(void)
{
  P2OUT &= ~BIT3;
  P2OUT &= ~BIT4;
  P2OUT &= ~BIT5;
}

void check_system(void)
{
  luminosity_sensor1 = (unsigned long)((read_sensor_one()*100)/1023);
  luminosity_sensor2 = (unsigned long)((read_sensor_two()*100)/1023);
  luminosity_average = ((luminosity_sensor1 + luminosity_sensor2)/2);
  
  if(luminosity_average <= 50)
  {
    P2OUT = BIT3;
    TA1CCR1 = SERVO_STEP_100;
    __delay_cycles(1000000);
    led[0] = 1;
    led[1] = 0;
    led[2] = 0;
    window = 100;
  }
  
  else if((luminosity_average >= 51) && (luminosity_average <= 65))
  {
    P2OUT = BIT4;
    TA1CCR1 = SERVO_STEP_50;
    __delay_cycles(1000000);
    led[0] = 0;
    led[1] = 1;
    led[2] = 0;
    window = 50;
  }
  
  else if((luminosity_average >= 66) && (luminosity_average <= 100))
  {
    P2OUT = BIT5;
    TA1CCR1 = SERVO_STEP_10;
    __delay_cycles(1000000);
    led[0] = 0;
    led[1] = 0;
    led[2] = 1;
    window = 10;
  }
  
  else
  {
    /* Does nothing */
  }
}

void send_message(void)
{
  sprintf( tx_buffer, "***************\r\n SENSOR_ONE: %lu\r\n SENSOR_TWO: %lu\r\n AVERAGE:    %lu\r\n LED_GREEN:  %d\r\n LED_YELLOW: %d\r\n LED_RED:    %d\r\n WINDOW:     %d%\r\n ***************\r\n", 
          luminosity_sensor1, 
          luminosity_sensor2,
          luminosity_average,
          led[0], 
          led[1], 
          led[2], 
          window);
  uart_send(tx_buffer);
}

unsigned long reference_time = 0;

int main(void)
{  
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW | WDTHOLD;
  
  DCOCTL = 0;
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;
  
  init_hw();
  timer_init();
  adc_init();
  config_interrupt();
  config_UART();
  
  TA1CCR1 = SERVO_STEP_0;
  __delay_cycles(1000000);
    
  LPM4;

  while (1)
  {    
    check_system();
    if((TA1CCR1 - reference_time) >= 2000)
    {
      send_message();
    }
    //__delay_cycles(2000000); 
  }
}

#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void)
{
  __delay_cycles(500000);
  if(!active)
  {
    active = 1;
    LPM4_EXIT;
    sprintf( tx_buffer, "%s", "System is active!\r\n\n");
    uart_send(tx_buffer);
    reference_time = TA1CCR1;
  }
  else
  {
    active = 0;
    leds_off();
    config_interrupt();
    //TA1CCR1 = SERVO_STEP_0;
    //__delay_cycles(1000000);
    LPM4;
  }
  P1IFG &= ~BIT4;                      // P1.4 IFG cleared    
}
