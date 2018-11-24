/*
* Dimmer.cpp
*
* Created: 24.11.2018 14:26:53
* Author: koval
*/

#include <Arduino.h>
#include <CyberLib.h> // ������� ���������� ��� �������
#include "Dimmer.h"

void  DetectUp();
void TimerInterrupt();
void  DetectDown();

int _zeroPin;
DimmerItem* _items;
int* _itemValues;
int _tic;

// default constructor
Dimmer::Dimmer(int zeroPin, DimmerItem* items, int* itemValues)
{
	_items = items;
	_itemValues = itemValues;
	_zeroPin = zeroPin;
	pinMode(zeroPin, INPUT);				// ����������� ���� �� ���� ��� ������������ ����������� ������� ����� ����
	attachInterrupt(0, DetectUp, FALLING);  // ��������� ������������ ���������� interrupt0 �� pin 2 �� ������ �������
	StartTimer1(TimerInterrupt, 40);        // ����� ��� ������ ������� ���
	StopTimer1();                           // ���������� ������
} //Dimmer

void Dimmer::UpdateItemValue(int* itemValues)
{
	_itemValues = itemValues;
}

//----------------------����������� ����������--------------------------
void TimerInterrupt()
{       // ���������� ������� ����������� ������ 40 ���
	_tic++;                       // �������
	for(int i=0; i< sizeof(_items); i++)
	{	 if (_tic <= _itemValues[i]) continue;	    // ���� ������� ����� �������� ���
		_items[i].UpdateValue(_itemValues[i]);
	}
	//digitalWrite(dimPin, 1);   // ������� ���
}

void  DetectUp()	 // ��������� �������� ���������� �� ����������� ���� �����
{
	_tic = 0;                                 // �������� �������
	ResumeTimer1();                          // ������������� ������
	attachInterrupt(0, DetectDown, RISING);  // ������������� ����������
}

void  DetectDown() // ��������� �������� ���������� �� ����������� ���� ������
{
	_tic = 0;                                 // �������� �������
	StopTimer1(); 							 // ���������� ������
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
