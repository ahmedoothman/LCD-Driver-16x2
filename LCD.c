/*
 * LCD.c
 *
 * Created: 6/22/2022 11:01:23 AM
 *  Author: Ahmed Othman
 */
#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "LCD.h"

void toggle_enable(char byte){

	if(byte == 'L' || byte == 'l'){
		SET_BIT(ControlPort,EN);
		_delay_us(1);
		RESET_BIT(ControlPort,EN);
		_delay_ms(2);
	}else if(byte == 'H' || byte == 'h'){
		SET_BIT(ControlPort,EN);
		_delay_us(1);
		RESET_BIT(ControlPort,EN);
		_delay_us(200);
	}else{
		//full Byte
		SET_BIT(ControlPort,EN);
		_delay_ms(2);
		RESET_BIT(ControlPort,EN);

	}

}
void set_LCD_BIT_MODE(int LCDMODE){
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
		DataPort = (DataPort & 0x0F) | ((cmnd<<4) & 0xF0);
		toggle_enable('L'); // toggle enable for LOW byte
	}else{
		//configure 8 bit mode
			DataPort = cmnd;
			RESET_BIT(ControlPort,RS); // RS = 0 so out on command register
			toggle_enable('F'); // toggle enable for High byte
	}

}
void init_LCD(){
	//set EN and RS as output
	ControlPortDir |= (1<<EN_Dir) |(1<<RS_Dir);
		if (LCDMODE_Global ==4)
		{
			// set DataPort from pin 4 to pin 7 as output
			DataPortDir |=0xF0;
			_delay_ms(20);
			Command_LCD(0x28);              /* 2 line, 5*7 matrix in 4-bit mode */
			Command_LCD(0x0C);              /* Display on cursor off*/
			Command_LCD(0x06);              /* Increment cursor (shift cursor to right)*/
			Command_LCD(0x01);              /* Clear display screen*/				/* send for 4 bit initialization of LCD  */
		}else if(LCDMODE_Global ==8){
			// set DataPort from pin 0 to pin 7 as output
			DataPortDir |=0xFF;
			Command_LCD(0x38); /* 2 line, 5*7 matrix in 8-bit mode */
			Command_LCD(0x01); /* Clear display screen*/
			Command_LCD(0x06); /* Increment cursor (shift cursor to right)*/
			Command_LCD(0x80);	/*force cursor to begining of 1st row*/
			Command_LCD(0x0C); /* Display on cursor off*/

		}else{
			//There is no such a mode
		}

}

void Write_Char_LCD( unsigned char data )
{
	_delay_ms(100);
	if (LCDMODE_Global == 4)
	{
		DataPort = (DataPort & 0x0F) | (data & 0xF0); /* sending upper nibble */
		SET_BIT(ControlPort,RS); // RS = 1 so out on data register
		toggle_enable('H'); // toggle enable for High byte

		DataPort = (DataPort & 0x0F) | ((data << 4) & 0xF0); /* sending lower nibble */
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
		_delay_ms(100);
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
void jump_second_Line(int beginning){

	if(beginning == 1){
		Command_LCD(0xC0);
	}else{
		Command_LCD(0xC2);
	}

}
void jump_first_Line(int beginning){
	if (beginning == 1)
	{
		Command_LCD(80);
	}else{
		Command_LCD(0xC1);
	}

}
void scroll_display_left_right(int number_of_cells ){
	int x;
	x=number_of_cells;
	while(x>0){
		_delay_ms(7000);
		Command_LCD(0x1C); //shift right
		x--;
	}
	x=number_of_cells;
	while(x>0){
		_delay_ms(7000);
		Command_LCD(0x18);//shift left
		x--;
	}
}
