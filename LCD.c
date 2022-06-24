/*
 * LCD.c
 *
 * Created: 6/22/2022 11:01:23 AM
 *  Author: Ahmed Othman
 */

#include "LCD.h"
#include <avr/io.h>
#include <avr/delay.h>
#include <stdio.h>
#include <stdlib.h>


void toggle_enable(char byte){
	_delay_us(100);
	if(byte == 'L' || byte == 'l'){
		SET_BIT(ControlPort,EN);
		_delay_ms(2);
		RESET_BIT(ControlPort,EN);
		_delay_ms(2);
	}else if(byte == 'H' || byte == 'h'){
		SET_BIT(ControlPort,EN);
		_delay_ms(2);
		RESET_BIT(ControlPort,EN);
		_delay_ms(2);
	}else{
		//full Byte
		SET_BIT(ControlPort,EN);
		_delay_ms(2);
		RESET_BIT(ControlPort,EN);
		_delay_ms(2);

	}

}

void Set_LCD_BIT_MODE(int LCDMODE){
	if(LCDMODE == 4 || LCDMODE == 8){
		LCDMODE_Global = LCDMODE;
	}else{
		//there is no such a mode
	}

}
void Command_LCD(unsigned char cmnd){
	if(LCDMODE_Global==4){
		//send the high byte of the command
		DataPort = (DataPort & 0x0F) | (cmnd & 0xF0);
		RESET_BIT(ControlPort,RS); // RS = 0 so out on command register
		toggle_enable('H'); // toggle enable for high byte
		//send the low byte of the command
		DataPort = (DataPort & 0x0F) | (cmnd<<4);
		toggle_enable('L'); // toggle enable for LOW byte
		//retry_command(cmnd);
	}else{
		//configure 8 bit mode
			DataPort = cmnd;
			RESET_BIT(ControlPort,RS); // RS = 0 so out on command register
			toggle_enable('F'); // toggle enable for Full byte
	}

}

void init_LCD(){
	_delay_ms(50);
	//set EN and RS as output
	ControlPortDir |= (1<<EN_Dir) |(1<<RS_Dir);
		if (LCDMODE_Global ==4)
		{
			// set DataPort from pin 4 to pin 7 as output
			DataPortDir |=0xF0;
			_delay_ms(20);
			Command_LCD(0x28);              /* 2 line, 5*7 matrix in 4-bit mode */
		}else if(LCDMODE_Global ==8){
			// set DataPort from pin 0 to pin 7 as output
			DataPortDir |=0xFF;
			_delay_ms(20);
			Command_LCD(0x38);  /* 2 line, 5*7 matrix in 8-bit mode */
		}else{
			//There is no such a mode
		}
			_delay_ms(10);
			Command_LCD(0x0C);              /* Display on cursor off*/
			_delay_ms(10);
			Command_LCD(0x06);              /* Increment cursor (shift cursor to right)*/
			_delay_ms(10);
			Command_LCD(0x80);				//force cusror to beginning of 1st row
			_delay_ms(10);
			Command_LCD(0x01);              /* Clear display screen*/

			if (LCDMODE_Global == 8)
			{
				re_try_init();
			}
			//re_try_init();
}

void re_try_init(){
		_delay_ms(20);
		Command_LCD(0x38);  /* 2 line, 5*7 matrix in 8-bit mode */
		_delay_ms(10);
		Command_LCD(0x0C);              /* Display on cursor off*/
		_delay_ms(10);
		Command_LCD(0x06);              /* Increment cursor (shift cursor to right)*/
		_delay_ms(10);
		Command_LCD(0x80);				//force cusror to beginning of 1st row
		_delay_ms(10);
		Command_LCD(0x01);              /* Clear display screen*/
}
void Write_Char_LCD( unsigned char data )
{
	_delay_us(10);
	if (LCDMODE_Global == 4)
	{
		DataPort = (DataPort & 0x0F) | (data & 0xF0); /* sending upper nibble */
		SET_BIT(ControlPort,RS); // RS = 1 so out on data register
		toggle_enable('H'); // toggle enable for High byte

		DataPort = (DataPort & 0x0F) | (data << 4); /* sending lower nibble */
		toggle_enable('L'); // toggle enable for LOW byte
	}else{
		//8-bit mode
		DataPort = data; /* sending upper nibble */
		SET_BIT(ControlPort,RS); // RS = 1 so out on data register
		toggle_enable('F'); // toggle enable for Full byte
	}

}

void Clear_LCD()
{
	Command_LCD(0x01);		/* Clear display */
	_delay_ms(2);
	Command_LCD(0x80);		/* Cursor at home position */
}
void Write_String_LCD (char *str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		Write_Char_LCD (str[i]);
		_delay_us(500);
	}
}
void Write_Num_LCD_Float(float num){
	char str[20];
	sprintf(str, "%.2f",num);
	Write_String_LCD(str);
}
void Write_Num_LCD_Int(int num){
	char str[20];
	sprintf(str, "%i",num);
	Write_String_LCD(str);
}

// send 1 if you want from beginning
void Jump_Second_Line(int beginning){

	if(beginning == 1){
		Command_LCD(0xC0);
	}else{
		Command_LCD(0xC2);
	}

}
void Jump_First_Line(int beginning){
	if (beginning == 1)
	{
		Command_LCD(80);
	}else{
		Command_LCD(0xC1);
	}

}
void Scroll_Display_Left_Right(int number_of_cells){
	int x;
	x=number_of_cells;
	while(x>0){
		_delay_ms(Scroll_Speed_Delay);
		Command_LCD(0x1C);
		x--;
	}
	x=number_of_cells;
	while(x>0){
		_delay_ms(Scroll_Speed_Delay);
		Command_LCD(0x18);
		x--;
	}
}

void Show_Cursor(){
	Command_LCD(0x0E);
}
void Hide_Cursor(){
	Command_LCD(0x0C);
}


void Set_Cursor_XY(int x,int y){
	if(x == 1){
		Command_LCD(0x80+y);
	}else if (x == 2)
	{
		Command_LCD(0xC0+y);
	}
}
void Delete_At_XY(int x,int y, int length_of_word){
	Set_Cursor_XY(x,y);
	for (int i = 0; i<length_of_word;i++)
	{
		Write_String_LCD(" ");
	}
}
