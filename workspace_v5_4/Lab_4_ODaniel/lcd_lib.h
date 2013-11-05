/*
 * lcd_lib.h
 *
 *  Created on: Oct 25, 2013
 *      Author: C15Craig.ODaniel
 */

#ifndef LCD_LIB_H_
#define LCD_LIB_H_

void initSPI();

void LCDinit();

void LCDclear();

void cursorToLineTwo();

void cursorToLineOne();

void writeChar(char asciiChar);

void writeString(char * string);

void scrollString(char * string1, char * string2);


#endif /* LCD_LIB_H_ */
