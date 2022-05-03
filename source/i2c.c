/**@file: i2c .c
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

#include "i2c.h"

int lock_detect = 0;
int i2c_lock = 0;

/**
 * @function I2C_init
 * @brief  	 Initialize the I2C0 module for KL25Z
 * @param    none
 * @return   none
 */
void I2C_init(void){
	//Enabling clock to I2C0 module and GPIO Port E
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

	//Set pins to I2C functionality
	PORTE->PCR[24] |= PORT_PCR_MUX(5);	//Setting I2C0_SCL pin configuration
	PORTE->PCR[25] |= PORT_PCR_MUX(5);	//Setting I2C0_SDA pin configuration

	I2C0->F = (I2C_F_MULT(0) | I2C_F_ICR(0X10));

	//Enable I2C and set it to master mode
	I2C0->C1 |= I2C_C1_IICEN_MASK;

	//Select high drive mode
	I2C0->C2 |= I2C_C2_HDRS_MASK;
}

/*
 * @function I2C_busy
 * @brief  	 This function checks the I2C line be busy or not
 * @param    none
 * @return   none
 */
void I2C_busy(void){
	lock_detect = 0;
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C0->C1 |= I2C_C1_TX_MASK;		//Set to transmit mode
	I2C0->C1 |= I2C_C1_MST_MASK;
	I2C0->C1 |= I2C_C1_IICEN_MASK;

	//Clear I2C line
	I2C0->C1 |= I2C_C1_MST_MASK;	//Set Master mode
	I2C0->C1 |= I2C_C1_TX_MASK;		//Set Transmitter mode
	I2C0->D = 0xFF;
	while((I2C0->S & I2C_S_IICIF_MASK) == 0U){
	}								//I2c wait interrupt
	I2C0->S |= I2C_S_IICIF_MASK;	//I2C clear interrupt

	I2C0->S |= I2C_S_ARBL_MASK;		//Clear arbitration

	I2C0->C1 &= ~I2C_C1_IICEN_MASK;	//Send start
//	I2C0->C1 |= I2C_C1_TX_MASK;		//set transmitter mode
	I2C0->C1 |= I2C_C1_MST_MASK;	//Start Sending signal

	I2C0->C1 |= I2C_C1_IICEN_MASK;

	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C0->C1 |= I2C_C1_MST_MASK;
	I2C0->C1 &= ~I2C_C1_MST_MASK;	//Set to slave mode
	I2C0->C1 &= ~I2C_C1_TX_MASK;	//Set Receiver mode
	I2C0->C1 |= I2C_C1_IICEN_MASK;

	I2C0->S |= I2C_S_IICIF_MASK;
	I2C0->S |= I2C_S_ARBL_MASK;		//Clear arbitration
	i2c_lock = 1;
}

/**
 * @function I2C_wait
 * @brief  	 This function waits till I2C is cleared
 * @param    none
 * @return   none
 */
void I2C_wait(void){
	lock_detect = 0;
	while(((I2C0->S & I2C_S_IICIF_MASK) == 0) & (lock_detect < 200)){
		lock_detect++;
	}
	if(lock_detect >= 200){
		I2C_busy();
	}
	I2C0->S |= I2C_S_IICIF_MASK;
}

/**
 * @function I2C_start
 * @brief  	 Begin I2C
 * @param    none
 * @return   none
 */
void I2C_start(void){
	I2C0->C1 |= I2C_C1_TX_MASK;
	I2C0->C1 |= I2C_C1_MST_MASK;
}

/**
 * @function I2C_read_setup
 * @brief  	 Configure the registers to read value register address and device address.
 *
 * @param    1. dev		Device address to read data
 * 			 2. Address	Address of the register to read data
 *
 * @return   none
 */
void I2C_read_setup(uint8_t dev, uint8_t address){
	I2C0->D = dev;					//Send device address
	I2C_wait();						// Wait till the line is cleared
	I2C0->D = address;				//Send read address
	I2C_wait();						// Wait till the I2C line is cleared
	I2C0->C1 |= I2C_C1_RSTA_MASK;	//Restart
	I2C0->D = (dev|0x1);			//Send device address for the value to be read
	I2C_wait();						// Wait till the I2C line is cleared
	I2C0->C1 &= ~I2C_C1_TX_MASK;	//Set to receive mode
}

/**
 * @function I2C_repeated_read
 * @brief  	 configure the I2C to configure the repeated read registers
 * @param    i2c_flag	indicating flag fot the function
 * @return   data to be read from register
 */
uint8_t I2C_repeated_read(uint8_t i2c_flag){
	uint8_t data;
	lock_detect = 0;

	if(i2c_flag){
		I2C0->C1 |= I2C_C1_TXAK_MASK;
	}
	else{
		I2C0->C1 &= ~I2C_C1_TXAK_MASK;
	}

	data = I2C0->D;					//Backup read data locally
	I2C_wait();						// Wait till the I2C line is cleared

	if(i2c_flag){
		I2C0->C1 &= ~I2C_C1_MST_MASK;
	}
	data = I2C0->D;					//Read data from the address

	return data;				// return the data to be read from the registers
}

/**
 * @function I2C_read_byte
 * @brief  	 configuration of the register to read the data in I2C
 * @param    1. dev		Device address to read data
 * 			 2. address	Address of the register to read data
 *
 * @return   data read from register
 */
uint8_t I2C_read_byte(uint8_t dev, uint8_t address){
	uint8_t data;

	I2C0->C1 |= I2C_C1_TX_MASK;		//Set to transmit mode
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;	//Send start
	I2C0->D = dev;					//Send device address
	I2C_wait();						//// Wait till the I2C line is cleared

	I2C0->D = address;				//Send read address
	I2C_wait();						//// Wait till the I2C line is cleared

	I2C0->C1 |= I2C_C1_RSTA_MASK;	//Repeated start
	I2C0->D = (dev|0x1);			//Send development address - read
	I2C_wait();						//// Wait till the I2C line is cleared

	I2C0->C1 &= ~I2C_C1_TX_MASK;	//Set to receive mode
	I2C0->C1 |= I2C_C1_TXAK_MASK;	//Set NACK after read

	data = I2C0->D;					//Read backup
	I2C_wait();						//// Wait till the I2C line is cleared

	I2C0->C1 &= ~I2C_C1_MST_MASK;	//Send stop
	data = I2C0->D;					//Read data

	return data;					//// return the data to be read from the registers
}

/**
 * @function I2C_write_byte
 * @brief  	 configuration I2C to write byte
 * @param   1. dev		Device address whre data is written
 * 			 2. address	Address of the register whre data is written
 *
 * 			 3. data		Data to be written
 * @return   none
 */
void I2C_write_byte(uint8_t dev, uint8_t address, uint8_t data){
	I2C0->C1 |= I2C_C1_TX_MASK;		//Set to transmit mode
	I2C0->C1 |= I2C_C1_MST_MASK;	//Send start
	I2C0->D = dev;					//Send device address
	I2C_wait();						//// Wait till the I2C line is cleared

	I2C0->D = address;				//Send write address
	I2C_wait();						//// Wait till the I2C line is cleared

	I2C0->D = data;					//Send data
	I2C_wait();						//// Wait till the I2C line is cleared
	I2C0->C1 &= ~I2C_C1_MST_MASK;	//Send stop bit
}
