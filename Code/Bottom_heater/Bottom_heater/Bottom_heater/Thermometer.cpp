/* 
* Thermometer.cpp
*
* Created: 14.11.2018 22:55:59
* Author: koval
*/


#include "Thermometer.h"
#include "max6675.h"

MAX6675 thermocouple (4, 5, 6);
// default constructor
Thermometer::Thermometer()
{
	int thermoDO = 4;
	int thermoCS = 5;
	int thermoCLK = 6;
} //Thermometer

double Thermometer:: Read() {
	// basic readout test, just print the current temp
	return thermocouple.readCelsius();
}

// default destructor
Thermometer::~Thermometer()
{
} //~Thermometer
