/*
 * LCD.h
 *
 * Created: 6/22/2022 11:01:10 AM
 *  Author: Ahmed Othman
 */


#ifndef LCD_H_
#define LCD_H_
#include "Header.h"

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
void set_LCD_BIT_MODE(int LCDMODE);
void Command_LCD(unsigned char cmnd);
void Write_Char_LCD(unsigned char data);
void Write_String_LCD (char *str);
void Write_Num_LCD_Float (float num);
void Write_Num_LCD_Int (int num);
void Clear_LCD();
void jump_first_Line(int beginning);
void jump_second_Line(int beginning);
void scroll_display_left_right(int number_of_cells);

#endif /* LCD_H_ */
