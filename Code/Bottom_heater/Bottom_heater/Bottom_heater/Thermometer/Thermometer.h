/*
* Thermometer.h
*
* Created: 14.11.2018 22:56:00
* Author: koval
*/
#include "max6675.h"

#ifndef __THERMOMETER_H__
#define __THERMOMETER_H__


class Thermometer
{
	//variables
	public:
	protected:
	private:
	MAX6675* _thermocouple;
	//functions
	public:
	Thermometer(int,int,int);
	~Thermometer();
	double Read();
	protected:
	private:
	Thermometer( const Thermometer &c );
	Thermometer& operator=( const Thermometer &c );

}; //Thermometer

#endif //__THERMOMETER_H__
