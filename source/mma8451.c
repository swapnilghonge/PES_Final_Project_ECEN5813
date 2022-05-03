/**@file: mma8451.c
 * @brief: this file contains the initialization of Acceleromter mma8451
 *			read_full_xyz reads the value from the register
 *			calibration: takes average value to calibrate the accelerometer
 *
 * @author: Swapnil Ghonge
 * @date: May 2nd 2022
 * @tools: MCUXpresso IDE and FRDM-KL25Z Development Board
 * @Credits: Embedded Systems Fundamentals with Arm Cortex-M based Microcontrollers by Alexander G.Dean
 * 			 https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/I2C-Demo/src/mma8451.c
*/
#include "mma8451.h"

int16_t acc_x=0, acc_y=0, acc_z=0;

/**
 * @function init_mma
 * @brief  	 Initialize accelerometer by configuring the registers
 * @param    none
 * @return   none
 */
int init_mma(void){
	//Set active mode, 14 bit samples and 800hz ODR
	I2C_write_byte(MMA_ADDR, REG_CTRL1, 0x01);
	return 1;
}

/**
 * @function read_full_xyz
 * @brief  	 Read acceleration values for x,y,z direction
 *
 * @param    none
 * @return   none
 */
void read_full_xyz(void){
	int i;
	uint8_t data[6];
	int16_t temp[3];

	I2C_start();
	I2C_read_setup(MMA_ADDR, REG_XHI);

	//Read five bytes in repeated mode
	for(i=0; i<5; i++){
		data[i] = I2C_repeated_read(0);
	}
	//Read last byte ending repeated mode
	data[i] = I2C_repeated_read(1);

	for(i=0; i<3; i++){
		temp[i] = (int16_t)((data[2*i]<<8) | data[2*i+1]);
	}

	//Align for 14 bits
	acc_x = temp[0]/4;
	acc_y = temp[1]/4;
	acc_z = temp[2]/4;


}

/**
 * @function read_xyz
 * @brief  	 Read the value from the register where the x, y and z direction
 * 			 are stored.
 * @param    none
 * @return   none
 */
void read_xyz(void){
	acc_x = (int8_t)I2C_read_byte(MMA_ADDR, REG_XHI);
	delay(100);
	acc_y = (int8_t)I2C_read_byte(MMA_ADDR, REG_YHI);
	delay(100);
	acc_z = (int8_t)I2C_read_byte(MMA_ADDR, REG_ZHI);
}

/**
 * @function calibrate
 * @brief  	 Calibrates the reading of the accelerometer. The
 * 			 function stores the value clearing the offset. It
 * 			 returns the average values for all 3 axis to a
 * 			 dedicated buffer.
 * @param    xval[in]	pointer to buffer to store 100 values of
 * 						x-axis.
 * 			 yval[in]	pointer to buffer to store 100 values of
 * 						y-axis.
 * 			 zval[in]	pointer to buffer to store 100 values of
 * 						z-axis.
 * 			 xavg[out]	returns the average of acc. along x-axis
 * 			 yavg[out]	returns the average of acc. along y-axis
 * 			 zavg[out]	returns the average of acc. along z-axis
 * @return   average values of acceleration along all the 3 axis
 */
void calibrate(int16_t *x, int16_t *y, int16_t *z, int *x_avg, int *y_avg, int *z_avg){
	int sum = 0, sum1 = 0, sum2 = 0;
	for(int i = 0; i<100; i++){
		read_full_xyz();
		x[i] = acc_x;
		sum = x[i] + sum;

		y[i] = acc_y;
		sum1 = y[i] + sum1;

		z[i] = acc_z;
		sum2 = z[i] + sum2;
	}
	delay(100);
	*x_avg = sum/100;


	*y_avg = sum1/100;


	*z_avg = sum2/100;

}
