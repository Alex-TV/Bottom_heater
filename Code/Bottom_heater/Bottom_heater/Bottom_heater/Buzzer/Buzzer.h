/*
* Buzzer.h
*
* Created: 03.12.2018 23:26:02
* Author: koval
*/
#include <SimpleTimer.h>

#ifndef __BUZZER_H__
#define __BUZZER_H__


class Buzzer
{
	//variables
	public:
	protected:
	private:

	
	//functions
	public:
	Buzzer(int);
	~Buzzer();
	void BuzzerOn(long);
	void Run();
	protected:
	private:
	Buzzer( const Buzzer &c );
	Buzzer& operator=( const Buzzer &c );
	
}; //Buzzer

#endif //__BUZZER_H__
