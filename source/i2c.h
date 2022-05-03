/**@file: i2c .h
 * @brief: This file contains all the function related to  i2c
 *			i2c_init this file contains all the configuration of registers
 *			i2c_busy checks if the i2c line is busy or not
 *			i2c_wait i2c wait till the line is cleared or not
 *			i2c_start starts the I2c Transfer and receive register
 *			i2c_read reads the value from specific address
 *			i2c_repeated_read reads value from specific address
 *			i2c_write write the data to specific device and memory location
 * @author: Swapnil Ghonge
 * @date: 	May 2nd 2022
 * @tools: MCUXpresso IDE and FRDM-KL25Z Development Board
 * @Credits: Embedded Systems Fundamentals with Arm Cortex-M based Microcontrollers by Alexander G.Dean
 * 			https://github.com/funkyguy4000/ARM-Programs/blob/master/Bare%20Metal/FRDM-KL25Z%20Accelerometer/src/i2c.c
 * 			https://www.nxp.com/docs/en/data-sheet/MMA8451Q.pdf
 * 			https://www.nxp.com/docs/en/data-sheet/KL25P80M48SF0.pdf
 *			https://learningmicro.wordpress.com/interfacing-lcd-with-kl25z-freedom-board/
 *			https://community.nxp.com/t5/Kinetis-Software-Development-Kit/Driving-16x2-LCD-using-KSDK-drivers/ta-p/1098903
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>
#include "MKL25Z4.h"
/**
 * @function I2C_init
 * @brief  	 Initialize the I2C0 module for KL25Z
 * @param    none
 * @return   none
 */
void I2C_init(void);

/*
 * @function I2C_busy
 * @brief  	 This function checks the I2C line be busy or not
 * @param    none
 * @return   none
 */
void I2C_busy(void);


/**
 * @function I2C_wait
 * @brief  	 This function waits till I2C is cleared
 * @param    none
 * @return   none
 */
void I2C_wait(void);

/**
 * @function I2C_start
 * @brief  	 Begin I2C
 * @param    none
 * @return   none
 */
void I2C_start(void);

/**
 * @function I2C_read_setup
 * @brief  	 Configure the registers to read value register address and device address.
 *
 * @param    1. dev		Device address to read data
 * 			 2. Address	Address of the register to read data
 *
 * @return   none
 */
void I2C_read_setup(uint8_t dev, uint8_t address);

/**
 * @function I2C_repeated_read
 * @brief  	 configure the I2C to configure the repeated read registers
 * @param    i2c_flag	indicating flag fot the function
 * @return   data to be read from register
 */
uint8_t I2C_repeated_read(uint8_t flag);

/**
 * @function I2C_read_byte
 * @brief  	 configuration of the register to read the data in I2C
 * @param    1. dev		Device address to read data
 * 			 2. address	Address of the register to read data
 *
 * @return   data read from register
 */
uint8_t I2C_read_byte(uint8_t dev, uint8_t address);

/**
 * @function I2C_write_byte
 * @brief  	 configuration I2C to write byte
 * @param   1. dev		Device address whre data is written
 * 			 2. address	Address of the register whre data is written
 *
 * 			 3. data		Data to be written
 * @return   none
 */
void I2C_write_byte(uint8_t dev, uint8_t address, uint8_t data);

#endif /* I2C_H_ */
