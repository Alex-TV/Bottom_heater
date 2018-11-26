/*
* Dimmer.cpp
*
* Created: 24.11.2018 14:26:53
* Author: koval
*/

#include <Arduino.h>
#include <SimpleTimer.h>
#include "Dimmer.h"

// default constructor
Dimmer::Dimmer(int zeroPin, DimmerItem* items, int* itemValues)
{
	_items = items;
	_itemValues = itemValues;
	_zeroPin = zeroPin;
	pinMode(zeroPin, INPUT);				// ����������� ���� �� ���� ��� ������������ ����������� ������� ����� ����
	attachInterrupt(0, (void(*)())&Dimmer::DetectUp, FALLING);  // ��������� ������������ ���������� interrupt0 �� pin 2 �� ������ �������
	_timer = new SimpleTimer();
	_timerId = _timer->setInterval(timerInterval,(void(*)())&Dimmer::TimerInterrupt);
	_timer->disable(_timerId);
	//StartTimer1(TimerInterrupt, 40);        // ����� ��� ������ ������� ���
	//StopTimer1();                           // ���������� ������
} //Dimmer


void Dimmer::UpdateItemValue(int* itemValues)
{
	_itemValues = itemValues;
}

void Dimmer::Update()
{
	_timer->run();
}

//----------------------����������� ����������--------------------------
void  Dimmer::TimerInterrupt() // ���������� ������� ����������� ������ 40 ���
{
	_tic++;                       // �������
	for(int i=0; i< sizeof(_items); i++)
	{	 if (_tic <= _itemValues[i]) continue;	    // ���� ������� ����� �������� ���
		_items[i].UpdateValue(_itemValues[i]);
	}
	//digitalWrite(dimPin, 1);   // ������� ���
}

void  Dimmer::DetectUp()	 // ��������� �������� ���������� �� ����������� ���� �����
{
	_tic = 0;                                 // �������� �������
	_timer->enable(_timerId);
	_timer->restartTimer(_timerId); // ������������� ������
	//ResumeTimer1();
	attachInterrupt(0, (void(*)())&Dimmer::DetectDown, RISING);  // ������������� ����������
}


void   Dimmer::DetectDown() // ��������� �������� ���������� �� ����������� ���� ������
{
	_tic = 0;                                 // �������� �������
	_timer->disable(_timerId);// ���������� ������d
	//StopTimer1();
	for(int i=0; i< sizeof(_items); i++)
	{
		_items[i].UpdateValue(0);  // �������� ���
	}
	//digitalWrite(dimPin, 0);
	attachInterrupt(0, (void(*)())&Dimmer::DetectUp, FALLING);   // ������������� ����������
}
//----------------------����������� ����������--------------------------
// default destructor
Dimmer::~Dimmer()
{
} //~Dimmer
