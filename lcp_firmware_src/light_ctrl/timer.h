/**
 ******************************************************************************
 * @file           : timer.h
 * @brief          : Header for timer.c file.
 *                   This file contains timer function definition
 ******************************************************************************
 * @attention 
 *
 ******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

/*********************************************************
    Public functions.
*********************************************************/
void timer_init(void);
int timer_get_tick(void);
void timer_reset_tick(void);

#endif /* TIMER_H_ */