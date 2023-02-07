/*
 * MCU_bringup_stewart.c
 *
 * Created: 2021-08-25 2:14:48 PM
 * Author : StewartPearson
 */ 

#define F_CPU		8000000UL // Clock speed

#include <avr/io.h>
#include <util/delay.h> //for delay function
#include <stdio.h>
#include <math.h>

#include "i2c.h"
#include "screen_cmds.h"

void ADC_Init()
{
	/* Make ADC port as input */
	/* Enable ADC, fr/128  */
	/* Vref: AREF, ADC channel: 0 */
	
}

int ADC_Read(char channel)
{
	volatile uint8_t Ain=0,AinLow=0;
	
	/* TODO:Set input channel to read (ADMUX)*/

	/* TODO:Start conversion (ADCSRA)*/
	
	/* TODO: wait until end of conversion interrupt is low (ADSRA) */
	
	_delay_us(10);
	/* TODO: Read lower byte (ADCL)*/
	
	/* TODO: Read higher 2 bits and 
	Multiply with weight (ADCH)*/
	
	// Combine upper and lower bits
	Ain = Ain + AinLow;				
	return(Ain);			/* Return digital value*/
}


void screen_init(void)
{
	// TODO: Initialize screen
 }

void screen_write_string(char string_to_write[])
{
	int letter=0;
	
	I2Csendcmd(SCREEN_ADDR, COMMAND_CLEAR_DISPLAY);
	I2Csendcmd(SCREEN_ADDR, COMMAND_SET_CURSOR_LINE_1);
	int current_line = COMMAND_SET_CURSOR_LINE_1;
	
	while(string_to_write[letter]!='\0')
	{
		if ((letter != 0) && (letter % LINE_LENGTH == 0))
		{
			if (current_line == COMMAND_SET_CURSOR_LINE_4){
				current_line = COMMAND_SET_CURSOR_LINE_1;// We've gone past the end of the line, go to the next one
				I2Csendcmd(SCREEN_ADDR, COMMAND_CLEAR_DISPLAY);
			}
			else
			current_line = current_line+0x20;
			I2Csendcmd(SCREEN_ADDR, current_line); // We've gone past the end of the line, go to the next one
		}
		
		I2Csenddatum(SCREEN_ADDR, string_to_write[letter]);
		letter++;
	}
}


int main(void)
{
	DDRD = 0xff; //PortD as output (only need PD6 for display)
	const int STR_LEN = 40;
	const float VREF = 3.3; // Measure this with a voltmeter
	volatile char string_to_write[STR_LEN];
	
	_delay_ms(5);
	PORTD = PORTD | (0<<PD6); // turn off
	_delay_ms(200);
	PORTD = PORTD | (1<<PD6); // turn on display
	_delay_ms(5);
	
	//Set up I2C
	I2Cinit(); // Done
	
	//Initialize display
	screen_init(); // TODO
	
	//Initialize ADC
	ADC_Init(); // TODO
		
	//Write some data to get started
	strncpy(string_to_write,"hello world",STR_LEN);
	screen_write_string(string_to_write);
	
	while (1)
	{
		_delay_ms(100); // sit idle
		
		// Read from ADC periodically to check the temperature
	}
}




