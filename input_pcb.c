/*
 * input_pcb.c
 *
 * Created: 30.10.2024 21:25:32
 *  Author: chris
 * 
 *                    GNU GENERAL PUBLIC LICENSE
 *                       Version 3, 29 June 2007
 *
 * Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.

 */ 
#include "input_pcb.h"
#include <pcf8574.h>
#include <stdint.h>
#include <stdbool.h>

#define LED_PIN			(7)
#define ENCODER_OFFSET	(4)
#define ENCODER_DIRECTION (4)
#define ENCODER_CLOCK (5)
#define ENCODER_BUTTON (6)

static uint8_t _portstate = 0;
void input_pcb_init()
{
	pcf8574_setPort(PCB_I2C_ADDRESS, 0xFF);
}

uint8_t input_pcb_refresh()
{
	_portstate = ~(pcf8574_getPort(PCB_I2C_ADDRESS));
	return _portstate;
}

uint8_t input_pcb_getButton()
{
	// get the raw state from the portexpander
	uint8_t _port = _portstate;
	uint8_t result = _port & 0x0F;
	result |= (_port & 0x40) >> 2;
	
	return result;
}

int8_t input_pcb_getEncoder()
{
	static uint8_t _old_state = 0;
	
	int8_t result = 0;
	
	// Port einlesen
	uint8_t _state = (_portstate>>ENCODER_OFFSET) & 0x03;
	
	if (!_state)
	{
		switch(_old_state)
		{
			case 1: result = -1; break;
			case 2: result = 1; break;
			default: result = 0;
		}
	}
	// preserve state for next call.
	_old_state = _state;
	return result;	
}

void input_pcb_setLED(bool state)
{
	uint8_t _port = pcf8574_getPort(PCB_I2C_ADDRESS);
	if (state)
	{
		_port &= ~(1<<LED_PIN);
	}
	else
	{
		_port |= (1<< LED_PIN);
	}
	pcf8574_setPort(PCB_I2C_ADDRESS, _port);
}