/*
* Dimmer.cpp
*
* Created: 24.11.2018 14:26:53
* Author: koval
*/

#include <Arduino.h>
#include "CyberLib.h"
#include "Dimmer.h"
#include "../Settings.h"

void DetectUp();
void DetectDown();
void TimerInterrupt();

int _tic;
DimmerItem *_itemUp;
DimmerItem *_itemDown;

int _itemUpValue = 0;
int _itemDownValue = 0;

// default constructor
Dimmer::Dimmer( DimmerItem *itemUp, DimmerItem *itemDown)
{
	_itemUp = itemUp;
	_itemDown = itemDown;
	pinMode(zeroPin, INPUT);
	attachInterrupt(0, DetectUp, RISING);
	StartTimer1(TimerInterrupt, dimmerTimerInterval);
	StopTimer1();
} //Dimmer

void Dimmer::UpdateItemValue(int itemUpValue, int itemDownValue)
{
	_itemUpValue = itemUpValue;
	_itemDownValue = itemDownValue;
}

void TimerInterrupt()
{
	_tic++;
	_itemUp->UpdateValue(_tic > (int)OUTPUT_MAX - _itemUpValue && _tic < (int)OUTPUT_MAX);
	_itemDown->UpdateValue(_tic > (int)OUTPUT_MAX - _itemDownValue && _tic < (int)OUTPUT_MAX);
}

void DetectUp()
{
	_tic = 0;
	ResumeTimer1();
	//attachInterrupt(0, DetectDown, FALLING);
}

void DetectDown()
{
	//	_tic = 0;
	//	StopTimer1();
	//	if (_tic > _itemUpValue)
	//	{
	//		_itemUp->UpdateValue(LOW);
	//	}
	//	_itemUp->UpdateValue(HIGH);
	//	_itemDown->UpdateValue(HIGH);
	//	attachInterrupt(0, DetectUp, FALLING);
}

// default destructor
Dimmer::~Dimmer()
{
} //~Dimmer
