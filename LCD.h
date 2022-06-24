/*
 * LCD.h
 *
 * Created: 6/22/2022 11:01:10 AM
 *  Author: Ahmed Othman
 */


#ifndef LCD_H_
#define LCD_H_

#include "Header.h"

#define F_CPU 16000000UL

#define ControlPortDir DDRC
#define RS_Dir DDC0
#define EN_Dir DDC1

#define ControlPort PORTC
#define RS PORTC0
#define EN PORTC1

#define Scroll_Speed_Delay 800
/*4-Bit Mode
From pin 4 to pin 7 to any PORT you specify in the following definition
 8 Bit Mode
 From pin 0 to pin 7 to any PORT you specify in the following definition
*/
#define DataPortDir DDRD
#define DataPort PORTD

volatile int LCDMODE_Global;
void init_LCD();
void Set_LCD_BIT_MODE(int LCDMODE);
void Command_LCD(unsigned char cmnd);
void Write_Char_LCD(unsigned char data);
void Write_String_LCD (char *str);
void Write_Num_LCD_Float (float num);
void Write_Num_LCD_Int (int num);
void Clear_LCD();
void Jump_First_Line(int beginning);
void Jump_Second_Line(int beginning);
void Scroll_Display_Left_Right(int number_of_cells);
void Show_Cursor();
void Hide_Cursor();
void Set_Cursor_XY(int x,int y);
void Delete_At_XY(int x,int y, int length_of_word);
#endif /* LCD_H_ */
