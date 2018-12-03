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

int _tic;
int _timerDimmerId;
SimpleTimer* _timerDimmer;
DimmerItem* _items;
int* _itemValues;
	
// default constructor
Dimmer::Dimmer(int zeroPin, DimmerItem* items, int* itemValues)
{
	_items = items;
	_itemValues = itemValues;
	_zeroPin = zeroPin;
	pinMode(zeroPin, INPUT);				// ����������� ���� �� ���� ��� ������������ ����������� ������� ����� ����
	attachInterrupt(0, DetectUp, FALLING);  // ��������� ������������ ���������� interrupt0 �� pin 2 �� ������ �������
	_timerDimmer = new SimpleTimer();
	_timerDimmerId = _timerDimmer->setInterval(timerInterval,TimerInterrupt);
	_timerDimmer->disable(_timerDimmerId);
	//StartTimer1(TimerInterrupt, 40);        // ����� ��� ������ ������� ���
	//StopTimer1();                           // ���������� ������
} //Dimmer


void Dimmer::UpdateItemValue(int* itemValues)
{
	_itemValues = itemValues;
}

void Dimmer::Update()
{
	_timerDimmer->run();
}

//----------------------����������� ����������--------------------------
void TimerInterrupt() // ���������� ������� ����������� ������ 40 ���
{
	_tic++;                       // �������
	for(int i=0; i< sizeof(_items); i++)
	{	 if (_tic <= _itemValues[i]) continue;	    // ���� ������� ����� �������� ���
		_items[i].UpdateValue(_itemValues[i]);
	}
	//digitalWrite(dimPin, 1);   // ������� ���
}

void DetectUp()	 // ��������� �������� ���������� �� ����������� ���� �����
{
	_tic = 0;                                 // �������� �������
	_timerDimmer->enable(_timerDimmerId);
	_timerDimmer->restartTimer(_timerDimmerId); // ������������� ������
	//ResumeTimer1();
	attachInterrupt(0, DetectDown, RISING);  // ������������� ����������
}


void DetectDown() // ��������� �������� ���������� �� ����������� ���� ������
{
	_tic = 0;                                 // �������� �������
	_timerDimmer->disable(_timerDimmerId);// ���������� ������d
	//StopTimer1();
	for(int i=0; i< sizeof(_items); i++)
	{
		_items[i].UpdateValue(0);  // �������� ���
	}
	//digitalWrite(dimPin, 0);
	attachInterrupt(0, DetectUp, FALLING);   // ������������� ����������
}
//----------------------����������� ����������--------------------------
// default destructor
Dimmer::~Dimmer()
{
} //~Dimmer
