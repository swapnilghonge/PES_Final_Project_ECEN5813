/**@file: timer.c
 * @brief: the function is used to set delay of the of msec
 *
 * @author: Swapnil Ghonge
 * @date: May 2nd 2022
 * Credits: https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code/Chapter_9/DMA_Examples/Source
 *	https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_9/DMA_Examples/Source/timers.c
 *	https://www.mouser.com/pdfdocs/FRDM-KL25Z.pdf
 * 	Class Lectures and Notes
 */

#include "timer.h"

ticktime_t Ticks;

/**
 * @brief: this Init function is used to configure the clock
 * by loading the counter value as per the requirement.
 * Here 10msec has been taken as 1 count value, hence load
 * value becomes (0.01 x 48000000)/16
 *
 * @param: NULL
 * @return: NULL
 */
void init_systick(void){
	SysTick->LOAD = (48000000/16/1000);				//Interrupt at every 1ms
	NVIC_SetPriority(SysTick_IRQn, 3);
	SysTick->VAL = 0;								//Force reloading the counter value
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk |		//Enable Systick timer
					SysTick_CTRL_ENABLE_Msk;
	NVIC_EnableIRQ(SysTick_IRQn);					//Enable Systick timer interrupt
}

/**
 * @brief: function checks if the capacitive sensor's
 * value if greater than the threshold.
 *
 * @param: NULL
 * @return: gives the current time since startup by returning
 * the value of timer. To get the correct time, timer should be multipled
 * by 10 since one count equals 10msec.
 */
ticktime_t now(){
	return Ticks;									//Returns time since startup
}

/**
 * @brief: function return the time passed since the last
 * call to reset
 *
 * @param: NULL
 * @return: returns ticks since the last call to Reset_Timer()
 */
void reset_timer(){
	SysTick->VAL = 0;								//Resetting the counter to 0
}

/**
 * @func	getTicks()
 * @brief	Gives the number of ticks since the boot of the program
 * @param	none
 * @return	ticktime_t	Number of ticks
 */
ticktime_t get_timer(){
	return SysTick->VAL;							//Return current counter
}

/**
 * @brief: function becomes active as soon as the Systick is enabled
 * keeps incrementing the values of timer and counter.
 *
 * @param: NULL
 * @return: NULL
 */
void SysTick_Handler(){
	Ticks++;				//Increment ticks on each interrupt
}

/**
 * @func	getTicks()
 * @brief	Gives the number of ticks since the boot of the program
 * @param	none
 * @return	ticktime_t	Number of ticks
 */
ticktime_t getTicks(){
	return Ticks;			//Retuns the Ticks counter to the main code
}

void delay(uint16_t delay){
	uint32_t current_time = getTicks();
	while((getTicks() - current_time) <= delay){
		__asm volatile ("nop");
	}
}
