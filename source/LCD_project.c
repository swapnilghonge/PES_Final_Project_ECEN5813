/*
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    LCD_Project.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "mma8451.h"
#include "timer.h"
#include "utility.h"
#include "lcd.h"
/* TODO: insert other definitions and declarations here. */
int16_t x[100] = {0};
int16_t y[100] = {0};
int16_t z[100] = {0};
int x_avg, y_avg, z_avg;
int16_t total_vect[100] = {0};
int16_t avg[100] = {0};
uint16_t step_count = 0;
uint16_t distance = 0;
uint16_t calorie = 0;
/*
 * @brief   Application entry point.
 */
int main(void) {

    /* Init board hardware. */
     BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    BOARD_InitDebugConsole();


    init_systick();
    I2C_init();

    if(!init_mma()){				//Initialize accelerometer
    	while(1);
    }
    lcd_init();				//initialize LCD


    calibrate(x, y, z, &x_avg, &y_avg, &z_avg);
    delay(1000);
/*****************Initialize LCD*****************/
    start_lcd();
    lcd_data_write("Fitness Track", LCD_LINE1);
    lcd_data_write("Use mma8451", LCD_LINE2);
    delay(2000);
    clear_lcd();								//Clear display
	lcd_data_write("Fitness Track", LCD_LINE1);
	delay(2000);
	clear_lcd();

    volatile static int i = 0 ;
    /************main while loop*****************/
    while(1)
    {
        i++ ;
        if(i<100){
        	step_count = step_detect(step_count, i);


        	distance = step_count*0.41;
        	lcd_data_write("distance:", LCD_LINE1);
        	lcd_data_write_int(distance, SAME_LINE);

/***********calorie measure Algorithm********************/

        	 if ((distance%2)==0)
        	{
        		 delay(2000);
        			calorie++;
        			lcd_data_write("calorie", LCD_LINE2);
        			lcd_data_write_int(calorie, SAME_LINE);
        	}
        }
        else
        {
        	i=0;
        }

    }
    return 0 ;
}
