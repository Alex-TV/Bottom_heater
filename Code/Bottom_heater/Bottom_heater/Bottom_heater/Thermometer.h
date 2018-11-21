/* 
* Thermometer.h
*
* Created: 14.11.2018 22:56:00
* Author: koval
*/


#ifndef __THERMOMETER_H__
#define __THERMOMETER_H__


class Thermometer
{
//variables
public:
protected:
private:

//functions
public:
	Thermometer();
	~Thermometer();
	double Read();
protected:
private:
	Thermometer( const Thermometer &c );
	Thermometer& operator=( const Thermometer &c );

}; //Thermometer

#endif //__THERMOMETER_H__
