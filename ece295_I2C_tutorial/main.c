/*
 * ece295_I2C_tutorial.c
 *
 * Created: 9/2/2021 5:38:25 PM
 * Author : amack
 */ 

#define F_CPU		8000000UL // Clock speed

#include <avr/io.h>
#include <util/delay.h> //for delay function
#include <stdio.h>

#include "i2c.h"
#include "screen_cmds.h"

int main(void)
{
	DDRA = 0xff; //PortA as output (only need PA0 for display)
	
	_delay_ms(5);
	PORTA = PORTA | (0<<PA0); // turn off
	_delay_ms(200);
	PORTA = PORTA | (1<<PA0); // turn on display
	_delay_ms(5);
	
	//Set up I2C
	I2Cinit();
	
	//Initialize display
	// ...
	
    //Write some data
	
    while (1) 
    {
    }
}

