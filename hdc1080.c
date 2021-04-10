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

#include "hdc1080.h"

#include "transfer_handler.h"

uint8_t hdc1080_conf_register;

static void hdc1080_write(uint8_t reg, uint16_t data)
{
		uint8_t sendbuf[3] = {reg, (data >> 8), data};
		iic_send(HDC1080_ADDR, sendbuf, 3, false);

}

static uint16_t hdc1080_read(uint8_t reg)
{
		uint8_t recvbuf[2];
		iic_send(HDC1080_ADDR, &reg, 1, false);
		
		delay(9);
		
		iic_read(HDC1080_ADDR, recvbuf, 2);
		
		return (recvbuf[0] << 8) | recvbuf[1];

}

uint16_t hdc1080_readManufacturerId(void){

		return hdc1080_read(HDC1080_MANUFACTURER_ID);

} 

uint16_t hdc1080_readDeviceId(void){

		return hdc1080_read(HDC1080_DEVICE_ID);

}

uint16_t hdc1080_readSerialNumber(uint8_t snpos){

		return hdc1080_read(snpos);

}

void hdc1080_begin(uint16_t resolution){
	
	ret_code_t err_code;
	hdc1080_write(HDC1080_CONFIGURATION, HDC1080_CONF_RESET);
	
	delay(2);
	
	hdc1080_conf_register = resolution & HDC1080_RESOLUTION_MASK;
	hdc1080_write(HDC1080_CONFIGURATION, hdc1080_conf_register);

}

void hdc1080_heater(bool en) {
	
	uint16_t sendbuf = hdc1080_conf_register;
	if(en)
		sendbuf |= HDC1080_CONF_HEAT;
	else
		sendbuf &= (~HDC1080_CONF_HEAT);
	
	hdc1080_write(HDC1080_CONFIGURATION, sendbuf);
	
}

float hdc1080_readTemperature(void){
	
	int16_t raw = hdc1080_read(HDC1080_TEMPERATURE);
	return (raw / 65536.0f) * 165.0f - 40.0f;
	
}

float hdc1080_readHumidity(void){
	
	int16_t raw = hdc1080_read(HDC1080_HUMIDITY);
	return (raw / 65536.0f) * 100.0f;
	
}
