/*
* Thermometer.cpp
*
* Created: 14.11.2018 22:55:59
* Author: koval
*/

#include "Thermometer.h"

// default constructor
Thermometer::Thermometer(int pinDO, int pinCS,int pinCLK)
{
	_thermocouple = new MAX6675(pinCLK, pinCS, pinDO);
	delay(500);
} //Thermometer

double Thermometer:: Read() {
	// basic readout test, just print the current temp
	return _thermocouple->readCelsius();
}

// default destructor
Thermometer::~Thermometer()
{
} //~Thermometer
