/***********
 * lcd.c
 * Author: Kevan Mordan
 * Date: 22 Oct 13
 ***********/

#include <msp430.h>
#include "lcd.h"

#define RS_MASK 0x40
 int LCDCON = 0x0;
 int LCDDATA = 0x0;
 int LCDSEND = 0x0;


void initSPI()
{
	UCB0CTL1 |= UCSWRST;

	UCB0CTL0 |= UCCKPH|UCMSB|UCMST|UCSYNC;

	UCB0CTL1 |= UCSSEL1;

	UCB0STAT |= UCLISTEN;

	P1SEL |= BIT5;
	P1SEL2 |= BIT5;

	P1SEL |= BIT6;
	P1SEL2 |= BIT6;

	P1SEL |= BIT7;
	P1SEL2 |= BIT7;

	UCB0CTL1 &= ~ UCSWRST;
}

void set_SS_lo()
{
	P1DIR |= BIT0;
	P1OUT &= ~BIT0;
}

void set_SS_hi()
{
	P1DIR |= BIT0;   //slave high
	P1OUT |= BIT0;
}

void delayMilli()
{
	_delay_cycles(1651);
}

void delayMicro()
{
	_delay_cycles(40);
}

void SPI_send(char byteToSend)
{
    volatile char readByte;

    set_SS_lo();

    UCB0TXBUF = byteToSend;

    while(!(UCB0RXIFG & IFG2))
    {
        // wait until you've received a byte
    }

    readByte = UCB0RXBUF;

    set_SS_hi();
}
void LCD_write_4( char byteToSend )
{
	unsigned char sendByte = byteToSend;

	sendByte &= 0x7F;

	sendByte |= LCDCON;

	SPI_send(sendByte);

	delayMilli();

	sendByte |= 0x80;

	SPI_send(sendByte);

	delayMilli();

	sendByte &= 0x7f;

	SPI_send(sendByte);

	delayMilli();

}

void LCD_write_8(char byteToSend)
{
    unsigned char sendByte = byteToSend;

    sendByte &= 0xF0;

    sendByte = sendByte >> 4;               // rotate to the right 4 times

    LCD_write_4(sendByte);

    sendByte = byteToSend;

    sendByte &= 0x0F;

    LCD_write_4(sendByte);
}
void writeCommandNibble(char commandNibble)
{
    LCDCON &= ~RS_MASK;
    LCD_write_4(commandNibble);
    delayMilli();
}

void writeCommandByte(char commandByte)
{
    LCDCON &= ~RS_MASK;
    LCD_write_8(commandByte);
    delayMilli();
}

void writeDataByte(char dataByte)
{
    LCDCON |= RS_MASK;
    LCD_write_8(dataByte);
    delayMilli();
}


void LCDinit()
{
    writeCommandNibble(0x03);

    writeCommandNibble(0x03);

    writeCommandNibble(0x03);

    writeCommandNibble(0x02);

    writeCommandByte(0x28);

    writeCommandByte(0x0C);

    writeCommandByte(0x01);

    writeCommandByte(0x06);

    writeCommandByte(0x01);

    writeCommandByte(0x02);

    SPI_send(0);
    delayMicro();
}


void LCDclear()
{
    writeCommandByte(1);
}

void LCDtop()
{
	writeCommandByte(2);
}
void LCDbottom()
{
	writeCommandByte(0xc0);
}

void writeChar( char charToWrite )
{
	//LCDSEND = charToWrite;
	//LCD_write_8( LCDSEND );
	//delayMilli();
	writeDataByte( charToWrite );

}

void writeString( char string[], int stringLength )
{

	int i;

	for( i=0; i<stringLength; i++ )
	{
		writeChar( string[i] );
	}
//	writeChar(string[0]);
//
//	i=1;
//
//	while( string[i] != '0' )
//	{
//		writeChar( string[i] );
//		i++;
//	}

}

void scrollString( char string[], int stringLength )
{
	int i = 0;
	int tempChar = string[0];
	for( i=0; i < stringLength; i++ )
	{
		string[i] = string[i+1];
	}
	string[stringLength-1] = tempChar;
}

