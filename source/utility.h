/**@file: utility.h
 * @brief: the function used to detect step takes by the person
 *
 * @author: Swapnil Ghonge
 * @date: May 2nd 2022
 * @tools: MCUXpresso IDE and FRDM-KL25Z Development Board
 * @Credits: Embedded Systems Fundamentals with Arm Cortex-M based Microcontrollers by Alexander G.Dean
 */
#ifndef UTILITY_H_
#define UTILITY_H_

#include <stdbool.h>
#include <math.h>
#include "mma8451.h"
#include "timer.h"
#include "i2c.h"

/**
 * @function detect_step
 * @brief  	 It implements the step detection algorithm based on
 * 			 the readings of the MMA8451 accelerometer.
 * @param    count	 step count to incremented
 * 			 i      	index for the buffer
 * @return   count		It determines the new step count in case if
 * 						step is taken or not.
 */
uint16_t step_detect(uint16_t count, int i);

#endif /* UTILITY_H_ */
