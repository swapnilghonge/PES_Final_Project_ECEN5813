/**@file: utility.c
 * @brief: the function used to detect step takes by the person
 *
 * @author: Swapnil Ghonge
 * @date: May 2nd 2022
 * @tools: MCUXpresso IDE and FRDM-KL25Z Development Board
 * @Credits: Embedded Systems Fundamentals with Arm Cortex-M based Microcontrollers by Alexander G.Dean
 */

#include "utility.h"


#define	STEP_THRES			2000
#define STEP_CHANGE_THRES	700

extern int16_t x[50];
extern int16_t y[50];
extern int16_t z[50];
extern int16_t total_vect[50];
extern int16_t avg[50];
extern int x_avg, y_avg, z_avg;
bool flag = false;

extern int16_t acc_x, acc_y, acc_z;

/**
 * @function step detect
 * @brief  	 It implements the step detection algorithm based on
 * 			 the readings of the MMA8451 accelerometer.
 * @param    count		 step count to incremented
 * 			 i      	index for the buffer
 * @return   count		It determines the new step count in case if
 * 						step is taken or not.
 */
uint16_t step_detect(uint16_t count, int i){
	read_full_xyz();

	total_vect[i] = sqrt(((acc_x - x_avg) * (acc_x - x_avg)) + ((acc_y - y_avg) *
						(acc_y - y_avg)) + ((acc_z - z_avg) * (acc_z - z_avg)));

	avg[i] = (total_vect[i] + total_vect[i - 1]) / 2 ;

	delay(100);
	if(((avg[i]>STEP_THRES))&& (flag == false))
			{
		count++;
		flag = true;
	}
	else if((avg[i] > STEP_THRES) && (flag == true)){
		//Don't count
		__asm volatile ("nop");
	}

	if((((avg[i] - avg[i-1]) > STEP_CHANGE_THRES)||
		((avg[i-1] - avg[i]) > STEP_CHANGE_THRES)) && (flag == true)){
		flag = false;
	}
	return count;
}
