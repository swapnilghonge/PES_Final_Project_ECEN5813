/**@file: mma8451.h
 * @brief: this file contains the initialization of Accelerometer mma8451
 *			read_full_xyz reads the value from the register
 *			calibration: takes average value to calibrate the accelerometer
 *
 * @author: Swapnil Ghonge
 * @date: May 2nd 2022
 * @tools: MCUXpresso IDE and FRDM-KL25Z Development Board
 * @Credits: Embedded Systems Fundamentals with Arm Cortex-M based Microcontrollers by Alexander G.Dean
 * 			 https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/I2C-Demo/src/mma8451.c
*/
#ifndef MMA8451_H_
#define MMA8451_H_

#include <stdint.h>
#include <stdio.h>
#include "MKL25Z4.h"
#include "mma8451.h"
#include "timer.h"
#include "i2c.h"

/************************************************
 * MMA8451 registration configuration
 ************************************************/
#define MMA_ADDR 0x3A

#define REG_XHI 0x01
#define REG_XLO 0x02
#define REG_YHI 0x03
#define REG_YLO 0x04
#define REG_ZHI	0x05
#define REG_ZLO 0x06

#define REG_WHOAMI 0x0D
#define REG_CTRL1  0x2A
#define REG_CTRL4  0x2D

#define WHOAMI 0x1A

/**
 * @function init_mma
 * @brief  	 Initialize accelerometer by configuring the registers
 * @param    none
 * @return   none
 */
int init_mma(void);

/**
 * @function read_full_xyz
 * @brief  	 Read acceleration values for x,y,z direction
 *
 * @param    none
 * @return   none
 */
void read_full_xyz(void);

/**
 * @function read_xyz
 * @brief  	 Read the value from the register where the x, y and z direction
 * 			 are stored.
 * @param    none
 * @return   none
 */
void read_xyz(void);

/**
 * @function calibrate
 * @brief  	 Calibrates the reading of the accelerometer. The
 * 			 function clears the offset in all x,y,z axis.
 * @param    xval[]	pointer to buffer to store values on x direction
 * 			 yval[]	pointer to buffer to store values on y direction
 * 			 zval[]	pointer to buffer to store values on z direction
 * 			 xavg[]	returns the average of acc. along x-axis
 * 			 yavg[]	returns the average of acc. along y-axis
 * 			 zavg[]	returns the average of acc. along z-axis
 * @return   average values of acceleration
 */
void calibrate(int16_t *x, int16_t *y, int16_t *z, int *x_avg, int *y_avg, int *z_avg);

#endif /* MMA8451_H_ */
