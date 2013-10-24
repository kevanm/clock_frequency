//
// lcd.h
// Author: Todd Branchflower
// Date: 17 October 2013
// Description: Library to interact with the Geek Box LCD.
//

#ifndef _LCD_H
#define _LCD_H

void initSPI();

void LCDinit();

void LCDclear();

void LCD_write_4( char byteToSend );

void LCD_write_8( char byteToSend );

void cursorToLineTwo();

void cursorToLineOne();

void writeChar(char asciiChar);

void writeString(char string[], int stringLength);

void scrollString(char string[], int stringLength);

// Here are some helper functions from my LCD.c
// I don't expose these in my header, but may be helpful to you.

void writeDataByte(char dataByte);
void writeCommandNibble(char commandNibble);
void writeCommandByte(char commandByte);
void LCDtop();
void LCDbottom();

#endif
