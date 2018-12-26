/*
* EepromExtension.cpp
*
* Created: 02.12.2018 19:26:49
* Author: koval
*/

#include <Arduino.h>
#include <EEPROM.h>
#include "EepromExtension.h"

// default constructor
EepromExtension::EepromExtension()
{
	_eepromWavgat = new EEPROMWavgat();
} //EepromExtension

// default destructor
EepromExtension::~EepromExtension()
{
} //~EepromExtension

uint8_t EepromExtension::Read(int address)
{
	#if defined(__LGT8FX8E__)
	return _eepromWavgat->read(address);
	#else
	return EEPROM.read(address);
	#endif
}

void EepromExtension::Write(int address, uint8_t val)
{
	#if defined(__LGT8FX8E__)
	_eepromWavgat->write(address,val);
	#else
	EEPROM.write(address,val);
	#endif
	Serial.print("Write address: ");
	Serial.print(address);
	Serial.print(" val: ");
	Serial.println(val);
}

void EepromExtension::Clear()
{
	for (int i = 0 ; i < EEPROM.length() ; i++)
	{
		#if defined(__LGT8FX8E__)
		_eepromWavgat->write(i,0);
		#else
		EEPROM.write(i,0);
		#endif
	}
}


void EepromExtension::Update(int address, uint8_t val)
{
	#if defined(__LGT8FX8E__)
	uint8_t saveVal = 	 _eepromWavgat->read(address);
	if(saveVal != val)
	{
		_eepromWavgat->write(address, val);
	}
	#else
	EEPROM.update(address,val);
	#endif
}

float EepromExtension::FloatRead(int address)
{
	uint8_t raw[4];
	for(uint8_t i = 0; i < 4; i++)
	{
		#if defined(__LGT8FX8E__)
		raw[i] = _eepromWavgat->read(address+i);
		#else
		raw[i] = EEPROM.read(address+i);
		#endif
	}
	float &val = (float&)raw;
	return val;
}

void EepromExtension::FloatWrite(int address, float val)
{
	uint8_t raw[4];
	(float&)raw = val;
	for(uint8_t i = 0; i < 4; i++)
	{
		#if defined(__LGT8FX8E__)
		_eepromWavgat->write(address+i, raw[i]);
		#else
		EEPROM.write(address+i, raw[i]);
		#endif
	}
}

unsigned long EepromExtension::ULongRead(int address)
{
	uint8_t raw[4];
	for(uint8_t i = 0; i < 4; i++)
	{
		#if defined(__LGT8FX8E__)
		raw[i] = _eepromWavgat->read(address+i);
		#else
		raw[i] = EEPROM.read(address+i);
		#endif
	}
	unsigned long &val = (unsigned long&)raw;
	return val;
}

void EepromExtension::ULongWrite(int address, unsigned long val)
{
	uint8_t raw[4];
	(unsigned long&)raw = val;
	for(uint8_t i = 0; i < 4; i++)
	{
		#if defined(__LGT8FX8E__)
		_eepromWavgat->write(address+i, raw[i]);
		#else
		EEPROM.write(address+i, raw[i]);
		#endif
	}
}

long EepromExtension::LongRead(int address)
{
	uint8_t raw[4];
	for(uint8_t i = 0; i < 4; i++)
	{
		#if defined(__LGT8FX8E__)
		raw[i] = _eepromWavgat->read(address+i);
		#else
		raw[i] = EEPROM.read(address+i);
		#endif
	}
	long &val = (long&)raw;
	return val;
}

void EepromExtension::LongWrite(int address, long val)
{
	uint8_t raw[4];
	(long&)raw = val;
	for(uint8_t i = 0; i < 4; i++)
	{
		#if defined(__LGT8FX8E__)
		_eepromWavgat->write(address+i, raw[i]);
		#else
		EEPROM.write(address+i, raw[i]);
		#endif
	}
}

unsigned int EepromExtension::UIntRead(int address)
{
	uint8_t raw[2];
	for(uint8_t i = 0; i < 2; i++)
	{
		#if defined(__LGT8FX8E__)
		raw[i] = _eepromWavgat->read(address+i);
		#else
		raw[i] = EEPROM.read(address+i);
		#endif
	}
	unsigned int &val = (unsigned int&)raw;
	return val;
}

void EepromExtension::UIntWrite(int address, unsigned int val)
{
	uint8_t raw[2];
	(unsigned int&)raw = val;
	for(uint8_t i = 0; i < 2; i++)
	{
		#if defined(__LGT8FX8E__)
		_eepromWavgat->write(address+i, raw[i]);
		#else
		EEPROM.write(address+i, raw[i]);
		#endif
	}
}

int EepromExtension::IntRead(int address)
{
	uint8_t raw[2];
	for(uint8_t i = 0; i < 2; i++)
	{
		#if defined(__LGT8FX8E__)
		raw[i] = _eepromWavgat->read(address+i);
		#else
		raw[i] = EEPROM.read(address+i);
		#endif
	}
	int &val = (int&)raw;
	return val;
}

void EepromExtension::IntWrite(int address, int val)
{
	uint8_t raw[2];
	(int&)raw = val;
	for(uint8_t i = 0; i < 2; i++)
	{
		#if defined(__LGT8FX8E__)
		_eepromWavgat->write(address+i, raw[i]);
		#else
		EEPROM.write(address+i, raw[i]);
		#endif
	}
}
