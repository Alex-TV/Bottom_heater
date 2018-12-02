/*
* EepromExtension.cpp
*
* Created: 02.12.2018 19:26:49
* Author: koval
*/

#include <EEPROM.h>
#include "EepromExtension.h"

// default constructor
EepromExtension::EepromExtension()
{
} //EepromExtension

// default destructor
EepromExtension::~EepromExtension()
{
} //~EepromExtension

uint8_t EepromExtension::Read(int address)
{
	EEPROM.read(address);
}

void EepromExtension::Write(int address, uint8_t val)
{
	EEPROM.write(address,val);
}

void EepromExtension::Update(int address, uint8_t val)
{
	EEPROM.update(address,val);
}

float EepromExtension::FloatRead(int address)
{
	uint8_t raw[4];
	for(uint8_t i = 0; i < 4; i++) raw[i] = EEPROM.read(address+i);
	float &val = (float&)raw;
	return val;
}

void EepromExtension::FloatWrite(int address, float val)
{
	uint8_t raw[4];
	(float&)raw = val;
	for(uint8_t i = 0; i < 4; i++) EEPROM.write(address+i, raw[i]);
}

unsigned long EepromExtension::ULongRead(int address)
{
	uint8_t raw[4];
	for(uint8_t i = 0; i < 4; i++) raw[i] = EEPROM.read(address+i);
	unsigned long &val = (unsigned long&)raw;
	return val;
}

void EepromExtension::ULongWrite(int address, unsigned long val)
{
	uint8_t raw[4];
	(unsigned long&)raw = val;
	for(uint8_t i = 0; i < 4; i++) EEPROM.write(address+i, raw[i]);
}

long EepromExtension::LongRead(int address)
{
	uint8_t raw[4];
	for(uint8_t i = 0; i < 4; i++) raw[i] = EEPROM.read(address+i);
	long &val = (long&)raw;
	return val;
}

void EepromExtension::LongWrite(int address, long val)
{
	uint8_t raw[4];
	(long&)raw = val;
	for(uint8_t i = 0; i < 4; i++) EEPROM.write(address+i, raw[i]);
}

unsigned int EepromExtension::UIntRead(int address)
{
	uint8_t raw[2];
	for(uint8_t i = 0; i < 2; i++) raw[i] = EEPROM.read(address+i);
	unsigned int &val = (unsigned int&)raw;
	return val;
}

void EepromExtension::UIntWrite(int address, unsigned int val)
{
	uint8_t raw[2];
	(unsigned int&)raw = val;
	for(uint8_t i = 0; i < 2; i++) EEPROM.write(address+i, raw[i]);
}

int EepromExtension::IntRead(int address)
{
	uint8_t raw[2];
	for(uint8_t i = 0; i < 2; i++) raw[i] = EEPROM.read(address+i);
	int &val = (int&)raw;
	return val;
}

void EepromExtension::IntWrite(int address, int val)
{
	uint8_t raw[2];
	(int&)raw = val;
	for(uint8_t i = 0; i < 2; i++) EEPROM.write(address+i, raw[i]);
}
