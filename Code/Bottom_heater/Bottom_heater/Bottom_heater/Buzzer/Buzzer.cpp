/*
* Buzzer.cpp
*
* Created: 03.12.2018 23:26:02
* Author: koval
*/
#include "Buzzer.h"

void BeepTimerInterrupt();
void FrequencyTimerInterrupt();

int _buzzerPin;
SimpleTimer* _timer;
int _timerId;
int _frequencyTimerId;
bool _heightBeep = true;
bool _beepStart = false;
// default constructor
Buzzer::Buzzer(int pin)
{
	_buzzerPin = 0;
	_buzzerPin = pin;
	_timer = new SimpleTimer();
	_timerId =_timer->setInterval(0, BeepTimerInterrupt);
	_frequencyTimerId =_timer->setInterval(1, FrequencyTimerInterrupt);
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
	_beepStart = true;
}

void BeepTimerInterrupt()
{
	_timer->disable(_timerId);
	_beepStart = false;
}

void FrequencyTimerInterrupt()
{
	_timer->restartTimer(_frequencyTimerId);
	if(!_beepStart && !_heightBeep) return;
	_heightBeep = !_heightBeep;
	digitalWrite(_buzzerPin,_heightBeep);
}
