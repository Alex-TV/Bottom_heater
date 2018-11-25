/*
* Dimmer.cpp
*
* Created: 24.11.2018 14:26:53
* Author: koval
*/

#include <Arduino.h>
#include <SimpleTimer.h>
#include "Dimmer.h"

void DetectUp();
void DetectDown();
void TimerInterrupt();

int _zeroPin;
DimmerItem* _items;
SimpleTimer* _timer;
int* _itemValues;
int _tic;
int _timerId;
// default constructor
Dimmer::Dimmer(int zeroPin, DimmerItem* items, int* itemValues)
{
	_items = items;
	_itemValues = itemValues;
	_zeroPin = zeroPin;
	pinMode(zeroPin, INPUT);				// настраиваем порт на вход для отслеживания прохождения сигнала через ноль
	attachInterrupt(0, DetectUp, FALLING);  // настроить срабатывание прерывания interrupt0 на pin 2 на низкий уровень
	_timer = new SimpleTimer();
	_timerId = _timer->setInterval(timerInterval,TimerInterrupt);
	_timer->disable(_timerId);
	//StartTimer1(TimerInterrupt, 40);        // время для одного разряда ШИМ
	//StopTimer1();                           // остановить таймер
} //Dimmer


void Dimmer::UpdateItemValue(int* itemValues)
{
	_itemValues = itemValues;
}

void Dimmer::Update()
{
	_timer->run();
}

//----------------------ОБРАБОТЧИКИ ПРЕРЫВАНИЙ--------------------------
void TimerInterrupt() // прерывания таймера срабатывают каждые 40 мкс
{
	_tic++;                       // счетчик
	for(int i=0; i< sizeof(_items); i++)
	{	 if (_tic <= _itemValues[i]) continue;	    // если настало время включать ток
		_items[i].UpdateValue(_itemValues[i]);
	}
	//digitalWrite(dimPin, 1);   // врубить ток
}

void DetectUp()	 // обработка внешнего прерывания на пересекание нуля снизу
{
	_tic = 0;                                 // обнулить счетчик
	_timer->enable(_timerId);
	_timer->restartTimer(_timerId); // перезапустить таймер
	//ResumeTimer1();
	attachInterrupt(0, DetectDown, RISING);  // перенастроить прерывание
}

void  DetectDown() // обработка внешнего прерывания на пересекание нуля сверху
{
	_tic = 0;                                 // обнулить счетчик
	_timer->disable(_timerId);// остановить таймерd
	//StopTimer1();
	for(int i=0; i< sizeof(_items); i++)
	{
		_items[i].UpdateValue(0);  // вырубить ток
	}
	//digitalWrite(dimPin, 0);
	attachInterrupt(0, DetectUp, FALLING);   // перенастроить прерывание
}
//----------------------ОБРАБОТЧИКИ ПРЕРЫВАНИЙ--------------------------
// default destructor
Dimmer::~Dimmer()
{
} //~Dimmer
