/*
* Dimmer.cpp
*
* Created: 24.11.2018 14:26:53
* Author: koval
*/

#include <Arduino.h>
#include <CyberLib.h>
#include "Dimmer.h"

void DetectUp();
void DetectDown();
void TimerInterrupt();

int _tic;
DimmerItem* _itemUp;
DimmerItem* _itemDown;

int _itemUpValue =0;
int _itemDownValue=0;

// default constructor
Dimmer::Dimmer(int zeroPin, DimmerItem* itemUp, DimmerItem* itemDown)
{
	_itemUp = itemUp;
	_itemDown = itemDown;
	_zeroPin = zeroPin;
	pinMode(zeroPin, INPUT);				// настраиваем порт на вход для отслеживания прохождения сигнала через ноль
	attachInterrupt(0, DetectUp, FALLING);  // настроить срабатывание прерывания interrupt0 на pin 2 на низкий уровень
	StartTimer1(TimerInterrupt, timerInterval);        // время для одного разряда ШИМ
	StopTimer1();                            // остановить таймер
} //Dimmer


void Dimmer::UpdateItemValue(int itemUpValue, int itemDownValue)
{
	_itemUpValue = itemUpValue;
	_itemDownValue = itemDownValue;
}

//----------------------ОБРАБОТЧИКИ ПРЕРЫВАНИЙ--------------------------
void TimerInterrupt() // прерывания таймера срабатывают каждые 40 мкс
{
	_tic++;                       // счетчик

	if (_tic >255- _itemUpValue) 	    // если настало время включать ток
	{
		_itemUp->UpdateValue(1);
	}
	if(_tic>255- _itemDownValue)
	{
		_itemDown->UpdateValue(1);
	}
}

void DetectUp()	 // обработка внешнего прерывания на пересекание нуля снизу
{
	_tic = 0;                                 // обнулить счетчик
	ResumeTimer1();
	attachInterrupt(0, DetectDown, RISING);  // перенастроить прерывание
}


void DetectDown() // обработка внешнего прерывания на пересекание нуля сверху
{
	_tic = 0;                                 // обнулить счетчик
	StopTimer1();

	_itemUp->UpdateValue(0);  // вырубить ток
	_itemDown->UpdateValue(0);  // вырубить ток

	attachInterrupt(0, DetectUp, FALLING);   // перенастроить прерывание
}
//----------------------ОБРАБОТЧИКИ ПРЕРЫВАНИЙ--------------------------
// default destructor
Dimmer::~Dimmer()
{
} //~Dimmer
