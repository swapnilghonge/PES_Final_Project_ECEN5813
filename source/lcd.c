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

#include "lcd.h"

/**
 * @function lcd_init
 * @brief  	 Initialize the GPIO to interface the 16x2 LCD over it.
 * 			 GPIO port E is used for configuration
 * @param    none
 * @return   none
 */
void lcd_init(void){
	//Enable clock to PORTC
	SIM->SCGC5 |= SIM_SCGC5_PORTC(1);

	//Enable and initialize all the GPIO pins
	PORTC->PCR[10] |= PORT_PCR_MUX(1);			//Configure PTC10
	PORTC->PCR[7] |= PORT_PCR_MUX(1);			//Configure PTC7
	PORTC->PCR[6] |= PORT_PCR_MUX(1);			//Configure PTC6
	PORTC->PCR[5] |= PORT_PCR_MUX(1);			//Configure PTC5
	PORTC->PCR[4] |= PORT_PCR_MUX(1);			//Configure PTC4
	PORTC->PCR[3] |= PORT_PCR_MUX(1);			//Configure PTC3
	PORTC->PCR[0] |= PORT_PCR_MUX(1);			//Configure PTC0

	//Configure all the pins as output
	GPIOC->PDDR |= (LCD_DB7 | LCD_DB6 | LCD_DB5 |
				LCD_DB4 | LCD_E | LCD_RS | LCD_RW);
}

/**
 * @function write_nibble
 * @brief  	 write 4 bits on the LCD DDRAM.
 *
 * @param    nibble		nibble to be written
 *
 * @return   none
 */
void write_nibble(uint8_t nibble){
	uint32_t gpio_temp;

	//Get GPIOC Data Register
	gpio_temp = GPIOC->PDOR;

	//Update the LCD data line DB7
	if(nibble & 0x80){
		gpio_temp |= LCD_DB7;
	}
	else{
		gpio_temp &= ~LCD_DB7;
	}

	//Update the LCD data line DB6
	if(nibble & 0x40){
		gpio_temp |= LCD_DB6;
	}
	else{
		gpio_temp &= ~LCD_DB6;
	}

	//Update the LCD data line DB5
	if(nibble & 0x20){
		gpio_temp |= LCD_DB5;
	}
	else{
		gpio_temp &= ~LCD_DB5;
	}

	//Update the LCD data line DB4
	if(nibble & 0x10){
		gpio_temp |= LCD_DB4;
	}
	else{
		gpio_temp &= ~LCD_DB4;
	}

	GPIOC->PDOR = gpio_temp;					//Write - Update data on GPIO Port C
}

/**
 * @function lcd_cmd
 * @brief  	 sends the command to the device and device to memory
 * @param    cmd	command to be sent to the lCD
 * @return   none
 */
void lcd_cmd(uint8_t cmd){
	GPIOC->PDOR &= ~LCD_RS;						//Select command register (RS=Low)
	GPIOC->PDOR &= ~LCD_RW;						//Select write operation (RW=Low)

	write_nibble(cmd & 0xF0);					//Write upper nibble

	//Generate High to Low pulse on EN pin
	GPIOC->PDOR |= LCD_E;						//EN = High
	delay(1);
	GPIOC->PDOR &= ~LCD_E;						//EN = Low
	delay(1);

	write_nibble((cmd<<4) & 0xF0);				//Write lower nibble

	//Generate High to Low pulse on EN pin
	GPIOC->PDOR |= LCD_E;						//EN = High
	delay(1);
	GPIOC->PDOR &= ~LCD_E;						//EN = Low
	delay(1);
}

/**
 * @function start_lcd
 * @brief 		Functions that sends command to the memory
 * 			 	to initialize the LCD and sets the position of cursor.
 *
 *
 * @param    none
 * @return   none
 */
void start_lcd(void){
	lcd_cmd(0x02);								//Moves the cursor to initial positions
	delay(10);
	lcd_cmd(0x28);								//Enable 4-bit, 2 line, 5x7 dots mode for characters
	delay(10);
	lcd_cmd(0x0C);								//Display ON, Cursor OFF
	delay(10);
	lcd_cmd(0x01);								//Clear display
	delay(10);
}

/**
 * @function clear_lcd
 * @brief  	 Clears the LCD and refreshes it
 * @param    none
 * @return   none
 */
void clear_lcd(void){
	lcd_cmd(0x01);								//Clear display
	delay(10);
}

/**
 * @function lcd_string_write
 * @brief  	 Writes the string on the display,
 * 			 string is passed to display on LCD	.
 *
 * @param    str	pointer to the char pointer
 * @return   cnt	count of Data to be displayed on LCD
 */
uint8_t lcd_string_write(char **str){
	uint8_t cnt = 0;							//Counting String length

	//Write the complete message
	while(**str && (cnt<16)){
		GPIOC->PDOR |= LCD_RS;					//Select data register for LCD
		GPIOC->PDOR &= ~LCD_RW;					//Select write mode

		write_nibble(**str & 0xF0);				//Writing upper nibble
		GPIOC->PDOR |= LCD_E;					//EN = High
		delay(1);
		GPIOC->PDOR &= ~LCD_E;					//EN = Low
		delay(1);

		write_nibble((**str << 4) & 0xF0);		//Writing upper nibble
		GPIOC->PDOR |= LCD_E;					//EN = High
		delay(1);
		GPIOC->PDOR &= ~LCD_E;					//EN = Low
		delay(1);

		(*str)++;								//Moving the pointer to next character
		cnt++;
		delay(10);
	}
	return cnt;
}

/**
 * @function lcd_data_write
 * @brief  	 function writes string to be written on the LCD.
 *
 * @param    data	char pointer to be printed
 *
 * 			 line	cursor line
 * @return   none
 */
void lcd_data_write(char *data, lcd_line line){
	uint8_t char_written;						//Actual no. of chars written on LCD
	char *temp = " ";							//Space to be filled for unused blocks on line

	//switch case which handles where the data is to be written
	switch(line){
	case LCD_LINE1:
		lcd_cmd(0x80);							//Move the cursor to the beginning of first line
		break;

	case LCD_LINE2:
		lcd_cmd(0xC0);							//Move the cursor to the beginning of second line
		break;

	case SAME_LINE:								//Writes on the same line where the cursor currently is
		break;
	}

	//Write data string to LCD (it returns how many characters are written)
	char_written = lcd_string_write(&data);
	while(char_written < 16){
		lcd_string_write(&temp);
		char_written++;
	}
}

/**
 * @function lcd_data_write_int
 * @brief  	 function which handles to write integer on
 * 			 the LCD. Converts the Integer to ASCII value.
 *
 * @param    num	Integer to be displayed on screen.
 * 			 line	on which line the integer is to be printed
 * @return   none
 */
void lcd_data_write_int(uint32_t num, lcd_line line){
	uint8_t byte[10] = {0};							//Handle 10 digit array
	uint8_t idx = 0;							//Index to preserve the state of byte array

	//switch case whre the lcd is to be initialized
	switch(line){
	case LCD_LINE1:
		lcd_cmd(0x80);							//Move the cursor to the beginning of first line
		break;

	case LCD_LINE2:
		lcd_cmd(0xC0);							//Move the cursor to the beginning of second line
		break;

	case SAME_LINE:								//Writes on the same line where the cursor currently is
		break;
	}

	//Recovering each digit from the input
	while(num != 0){
		byte[idx] = num % 10;
		num = num / 10;
		idx++;
	}

	//Convert the decimal into ASCII and print on the LCD
	for(int i=(idx - 1); i>=0; i--){
		GPIOC->PDOR |= LCD_RS;					//Select data register
		GPIOC->PDOR &= ~LCD_RW;					//Select write mode

		write_nibble(('0'+byte[i]) & 0xF0);		//Write upper nibble
		GPIOC->PDOR |= LCD_E;					//EN = High
		delay(1);
		GPIOC->PDOR &= ~LCD_E;					//EN = Low
		delay(1);

		write_nibble((('0'+byte[i]) << 4) & 0xF0);	//Write lower nibble
		GPIOC->PDOR |= LCD_E;					//EN = High
		delay(1);
		GPIOC->PDOR &= ~LCD_E;					//EN = Low
		delay(1);

		delay(10);
	}
	if(idx == 0){
		GPIOC->PDOR |= LCD_RS;					//Select data register
		GPIOC->PDOR &= ~LCD_RW;					//Select write mode

		write_nibble(('0'+byte[idx]) & 0xF0);		//Write upper nibble
		GPIOC->PDOR |= LCD_E;					//EN = High
		delay(1);
		GPIOC->PDOR &= ~LCD_E;					//EN = Low
		delay(1);

		write_nibble((('0'+byte[idx]) << 4) & 0xF0);	//Write lower nibble
		GPIOC->PDOR |= LCD_E;					//EN = High
		delay(1);
		GPIOC->PDOR &= ~LCD_E;					//EN = Low
		delay(1);

		delay(10);
	}
}
