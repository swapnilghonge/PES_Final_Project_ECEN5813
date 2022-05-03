/**@file: timer.h
 * @brief: the function is used to set delay of the of msec
 *
 * @author: Swapnil Ghonge
 * @date: May 2nd 2022
 * Credits: https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code/Chapter_9/DMA_Examples/Source
 *	https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_9/DMA_Examples/Source/timers.c
 *	https://www.mouser.com/pdfdocs/FRDM-KL25Z.pdf
 * 	Class Lectures and Notes
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>
#include "MKL25Z4.h"

typedef uint32_t ticktime_t;

/**
 * @brief: this Init function is used to configure the clock
 * by loading the counter value as per the requirement.
 * Here 10msec has been taken as 1 count value, hence load
 * value becomes (0.01 x 48000000)/16
 *
 * @param: NULL
 * @return: NULL
 */
void init_systick(void);

/**
 * @brief: function checks if the capacitive sensor's
 * value if greater than the threshold.
 *
 * @param: NULL
 * @return: gives the current time since startup by returning
 * the value of timer. To get the correct time, timer should be multipled
 * by 10 since one count equals 10msec.
 */
ticktime_t now();

/**
 * @brief: function stores the current time in reset variable.
 *
 * @param: NULL
 * @return: NULL
 */
void reset_timer();

/**
 * @brief: function return the time passed since the last
 * call to reset
 *
 * @param: NULL
 * @return: returns ticks since the last call to Reset_Timer()
 */
ticktime_t get_timer();

/**
 * @func	getTicks()
 * @brief	Gives the number of ticks since the boot of the program
 * @param	none
 * @return	ticktime_t	Number of ticks
 */
ticktime_t getTicks();


void delay(uint16_t delay);

#endif /* TIMER_H_ */
