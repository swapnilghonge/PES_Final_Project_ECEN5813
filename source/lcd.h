/**@file: lcd.c
 * @brief: the function is used to initialize the LCD and read and write the data
 * 			lcd_init configures the registers to initiaze the lcd
 * 			write_nibble write 4 bytes in DDRAM
 *			lcd_cmd sends the data that writes to memory
 *			lcd_start initializes the cursor on the lcd
 *			clear_lcd clears the LCD by configuring the data registers
 *			Lcd_string writes the string to be displayed on the LCD
 *			lcd_write to write at specific location on LCD
 *			lcd_write int write the integer value on LCD
 *
 * @author: Swapnil Ghonge
 * @date: May 2nd 2022
 * @tools: MCUXpresso IDE and FRDM-KL25Z Development Board
 * @Credits: Embedded Systems Fundamentals with Arm Cortex-M based Microcontrollers by Alexander G.Dean
 * 			https://learningmicro.wordpress.com/interfacing-lcd-with-kl25z-freedom-board/
 * 			https://os.mbed.com/questions/50539/How-to-use-lcd-with-i2c-in-kl25z-platfor/
 *			https://codingstuffweb.wordpress.com/2017/02/04/frdm-kl25z-i2c-lcd/
 *			https://mcuoneclipse.com/2012/12/22/hd44780-2x16-character-display-for-kinetis-and-freedom-board/
 *			https://www.youtube.com/watch?v=n9TTmNu1vcw&ab_channel=BmeBuilds
 *			https://www.youtube.com/watch?v=jiqP185kq0c&ab_channel=Jfetronic%3AElectr%C3%B3nicayM%C3%A1s
 */
#ifndef LCD_H_
#define LCD_H_

#include "MKL25Z4.h"
#include "timer.h"


 // LCD to GPIO pin configuration interface

#define LCD_DB7  ((uint32_t)1 << 7)  // PTC7
#define LCD_DB6  ((uint32_t)1 << 0)  // PTC0
#define LCD_DB5  ((uint32_t)1 << 3)  // PTC3
#define LCD_DB4  ((uint32_t)1 << 4)  // PTC4

#define LCD_E    ((uint32_t)1 << 5)  // PTC5
#define LCD_RW   ((uint32_t)1 << 6)  // PTC6
#define LCD_RS   ((uint32_t)1 << 10) // PTC10

//lcd_line denotes the line number on the LCD.
typedef enum{
	LCD_LINE1,
	LCD_LINE2,
	SAME_LINE
}lcd_line;

/**
 * @function lcd_init
 * @brief  	 Initialize the GPIO to interface the 16x2 LCD over it.
 * 			 GPIO port E is used for configuration
 * @param    none
 * @return   none
 */
void lcd_init(void);

/**
 * @function write_nibble
 * @brief  	 write 4 bits on the LCD DDRAM.
 *
 * @param    nibble		nibble to be written
 *
 * @return   none
 */
void write_nibble(uint8_t nibble);

/**
 * @function lcd_cmd
 * @brief  	 sends the command to the device and device to memory
 * @param    cmd	command to be sent to the lCD
 * @return   none
 */
void lcd_cmd(uint8_t cmd);

/**
 * @function start_lcd
 * @brief 		Functions that sends command to the memory
 * 			 	to initialize the LCD and sets the position of cursor.
 *
 *
 * @param    none
 * @return   none
 */
void start_lcd(void);

/**
 * @function clear_lcd
 * @brief  	 Clears the LCD and refreshes it
 * @param    none
 * @return   none
 */
void clear_lcd(void);

/**
 * @function lcd_string_write
 * @brief  	 Writes the string on the display,
 * 			 string is passed to display on LCD	.
 *
 * @param    str	pointer to the char pointer
 * @return   cnt	count of Data to be displayed on LCD
 */
uint8_t lcd_string_write(char **str);

/**
 * @function lcd_data_write
 * @brief  	 function writes string to be written on the LCD.
 *
 * @param    data	char pointer to be printed
 *
 * 			 line	cursor line
 * @return   none
 */
void lcd_data_write(char *data, lcd_line line);

/**
 * @function lcd_data_write_int
 * @brief  	 function which handles to write integer on
 * 			 the LCD. Converts the Integer to ASCII value.
 *
 * @param    num	Integer to be displayed on screen.
 * 			 line	on which line the integer is to be printed
 * @return   none
 */
void lcd_data_write_int(uint32_t num, lcd_line line);

#endif /* LCD_H_ */
