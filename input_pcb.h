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

 * PCF8574 PINOUT
 *                         +---\/---+
 * GND              A0     |1*     8|      VCC
 * GND              A1     |2      7|      SDA
 * GND              A2     |3      6|      SCL
 * Button 0         P0     |4      5|      INT
 * Button 1         P1     |2      7|      P7      LED
 * Button 2         P2     |3      6|      P6      Encoder B
 * Button 3         P3     |4      5|      P5      Encoder A
 *                  GND    |4      5|      P4      Encoder Button
 *                         +--------+
 */ 


#ifndef INPUT_PCB_H_
#define INPUT_PCB_H_

// Default address of PCF8574 is 0x20
#define PCB_I2C_ADDRESS PCF8574_ADDRBASE

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif	
	
/**
 * Set all pins to high level.
 * TODO: i2c initialization
 */
void input_pcb_init();

/**
 * Read the pinstate of all port pins.
 * Pressed Button is represented as high.
 * @return uint8_t
 */
uint8_t input_pcb_refresh();

/**
 * Read the Buttons
 * @return uint8_t
 */
uint8_t input_pcb_getButton();

/**
 * Read the Encoder
 * @return int8_t (CW = 1, CCW = -1)
 */
int8_t input_pcb_getEncoder();

/**
 * 
 * Set the LED state
 * @brief Every Read from this chip will reset the Interrupt Flag!
 * @param state: bool
 */
void input_pcb_setLED(bool state);

#ifdef __cplusplus
}
#endif
#endif /* INPUT_PCB_H_ */