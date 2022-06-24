/*
 * LCD.c
 *
 * Created: 6/22/2022 11:00:51 AM
 * Author : Ahmed Othman
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/delay.h>
int main(void)
{	int x =9;
    /* Replace with your application code */
	set_LCD_BIT_MODE(8); //set mode to 8 bit
	init_LCD();

	Write_String_LCD("Hello World");
	//Write_Num_LCD_Int(200);
	jump_second_Line(1);
	Write_String_LCD("Bye");
    while (1)
    {
		scroll_display_left_right(5);
    }
}
