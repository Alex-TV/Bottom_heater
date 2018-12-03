/*
* Dimmer.h
*
* Created: 24.11.2018 14:26:53
* Author: koval
*/
#include "DimmerItem.h"
#define timerInterval 40

#ifndef __DIMMER_H__
#define __DIMMER_H__

class Dimmer
{
	//variables
	public:
	protected:
	private:
	int _zeroPin;
	
	


	//functions
	public:
	Dimmer(int, DimmerItem*, int*);
	~Dimmer();
	void UpdateItemValue(int*);
	void Update();
	protected:
	private:
	Dimmer( const Dimmer &c );
	Dimmer& operator=( const Dimmer &c );
	
}; //Dimmer

#endif //__DIMMER_H__
