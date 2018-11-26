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
	DimmerItem* _items;
	SimpleTimer* _timer;
	int* _itemValues;
	int _tic;
	int _timerId;
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
	void DetectUp();
	void DetectDown();
	void TimerInterrupt();
	
}; //Dimmer

#endif //__DIMMER_H__
