/*

Arduino Library for Texas Instruments HDC1080 Digital Humidity and Temperature Sensor
Written by AA for ClosedCube
---

The MIT License (MIT)

Copyright (c) 2016-2017 ClosedCube Limited

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#ifndef _CLOSEDCUBE_HDC1080_h
#define _CLOSEDCUBE_HDC1080_h

#include <stdint.h>
#include <stdbool.h>

#define HDC1080_ADDR 0x40

//HDC1080 Register
#define	HDC1080_TEMPERATURE 			0x00
#define	HDC1080_HUMIDITY 					0x01
#define	HDC1080_CONFIGURATION  		0x02
#define	HDC1080_MANUFACTURER_ID  	0xFE
#define	HDC1080_DEVICE_ID 				0xFF 
#define	HDC1080_SERIAL_ID_FIRST 	0xFB
#define	HDC1080_SERIAL_ID_MID 		0xFC
#define	HDC1080_SERIAL_ID_LAST 		0xFD

//HDC1080 CONF
#define HDC1080_CONF_RESET 				0x8000
#define HDC1080_CONF_HEAT					0x2000
#define HDC1080_CONF_SEQACQ       0x1000
#define HDC1080_CONF_BTST         0x0800

#define HDC1080_CONF_TRES_14BIT   0x0000
#define HDC1080_CONF_TRES_11BIT   0x0400

#define HDC1080_CONF_HRES_14BIT   0x0000
#define HDC1080_CONF_HRES_11BIT   0x0100
#define HDC1080_CONF_HRES_8BIT    0x0200

#define HDC1080_RESOLUTION_MASK   0x0700

uint16_t hdc1080_readManufacturerId(void); 	// 0x5449 ID of Texas Instruments
uint16_t hdc1080_readDeviceId(void);	   		// 0x1050 ID of the device
uint16_t hdc1080_readSerialNumber(uint8_t snpos);

void hdc1080_begin(uint16_t resolution);
void hdc1080_heater(bool en);

float hdc1080_readTemperature(void);
float hdc1080_readHumidity(void);

#endif
