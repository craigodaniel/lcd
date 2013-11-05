/*
 * lcd_lib.c
 *
 *  Created on: Oct 28, 2013
 *      Author: C15Craig.ODaniel
 */

#include <msp430.h>
#include "lcd_lib.h"


#define RS_MASK 0x40

void writeDataByte(char dataByte);
void writeCommandNibble(char commandNibble);
void writeCommandByte(char commandByte);
void LCD_write_8(char byteToSend);
void SPI_send(char byteToSend);
void delayMicro();
void delayMilli();
void set_SS_lo();
void set_SS_hi();
char LCDCON = 0;
void LCD_write_4(char byteToSend);

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

void delayMicro(){
	_delay_cycles(35);
}

void delayMilli(){
	_delay_cycles(1414);
}

void set_SS_lo(){
	P1OUT &= ~BIT0;
}

void set_SS_hi(){
	P1OUT |= BIT0;
}

void initSPI(){

	P1DIR |= BIT0;

	UCB0CTL1 |= UCSWRST;
	UCB0CTL0 |= UCCKPL|UCMSB|UCMST|UCSYNC;
	UCB0CTL1 |= UCSSEL1;
	UCB0STAT |= UCLISTEN;
	P1SEL |= BIT5;
	P1SEL2 |= BIT5;
	P1SEL |= BIT7;
	P1SEL2 |= BIT7;
	P1SEL |= BIT6;
	P1SEL2 |= BIT6;
	UCB0CTL1 &= ~UCSWRST;
}


void cursorToLineOne(){
	writeCommandByte(0x80);
}

void cursorToLineTwo(){
	writeCommandByte(0xc0);
}

void LCD_write_4(char byteToSend){
    unsigned char sendByte = byteToSend;
    sendByte &= 0x0f;
    sendByte |= LCDCON;
    sendByte &= 0x7f;
    SPI_send(sendByte);
    delayMicro();
    sendByte |= 0x80;
    SPI_send(sendByte);
    delayMicro();
    sendByte &= 0x7f;
    SPI_send(sendByte);
    delayMicro();
}


/*
 * Code below is from Capt Branchflower's LCD driver on github.com
 */
void writeChar(char asciiChar)
{
	writeDataByte(asciiChar);
}

void writeString(char * string)
{
	unsigned char charsPrinted = 0;
	while ((*string !=0) &&(charsPrinted < 8))
	{
		writeChar(*string);
		string++;
		charsPrinted++;
	}
}

char * printFromPosition(char * start, char * current, char screenSizeInChars)
{
	char * display;
	int i;

	if (*current == 0)
		current = start;

	display = current;

	for (i = 0; i < screenSizeInChars; i++){
		writeDataByte(*display);
		display++;

		if (*display ==0)
			display = start;
	}

	return current +1;
}

void scrollString(char * string1, char * string2)
{
	char * current1 = string1;
	char * current2 = string2;

	while (1)
	{
		current1 = printFromPosition(string1, current1, 8);
		cursorToLineTwo();
		current2 = printFromPosition(string2, current2, 8);
		cursorToLineOne();
		_delay_cycles(500000);
	}
}
