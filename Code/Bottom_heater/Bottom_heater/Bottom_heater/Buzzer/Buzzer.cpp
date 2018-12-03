/*
* Buzzer.cpp
*
* Created: 03.12.2018 23:26:02
* Author: koval
*/
#include "Buzzer.h"

void BeepTimerInterrupt();

int _buzzerPin;
SimpleTimer* _timer;
int _timerId;
// default constructor
Buzzer::Buzzer(int pin)
{
	_buzzerPin = 0;
	_buzzerPin = pin;
	_timer = new SimpleTimer();
	_timerId =_timer->setInterval(0, BeepTimerInterrupt);
	_timer->disable(_timerId);
	pinMode(pin, OUTPUT);
} //Buzzer

// default destructor
Buzzer::~Buzzer()
{
} //~Buzzer

void Buzzer::Run()
{
	_timer->run();
}

void Buzzer::BuzzerOn(long beepTime)
{
	_timer->enable(_timerId);
	_timer->updateInterval(_timerId, beepTime);
	_timer->restartTimer(_timerId);
	analogWrite(_buzzerPin,127);
}

void BeepTimerInterrupt()
{
	_timer->disable(_timerId);
	analogWrite(_buzzerPin,0);
}
