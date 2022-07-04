/*
 * LCD.c
 *
 * Created: 6/22/2022 11:00:51 AM
 * Author : Ahmed Othman
 */

#include "LCD.h"
#include <avr/io.h>
#include <avr/delay.h>
int main(void)
{	float x = 2;
    /* Replace with your application code */
	//_delay_ms(2000);
	Set_LCD_BIT_MODE(8); //set mode to 8 bit
	init_LCD();
	//init_LCD();
	Show_Cursor();
	Write_String_LCD("Count Secounds");
	Set_Cursor_XY(2,0);
	Write_String_LCD("Counts : ");
	Set_Cursor_XY(2,7);
	Write_Num_LCD_Int(2);
    while (1)
    {
	Set_Cursor_XY(2,7);
	Write_Num_LCD_Int(x);
	_delay_ms(1000);
	x +=1;
	Delete_At_XY(2,7,4);
    }
}
