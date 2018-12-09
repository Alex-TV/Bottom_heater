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
	pinMode(zeroPin, INPUT);				// ����������� ���� �� ���� ��� ������������ ����������� ������� ����� ����
	attachInterrupt(0, DetectUp, FALLING);  // ��������� ������������ ���������� interrupt0 �� pin 2 �� ������ �������
	StartTimer1(TimerInterrupt, timerInterval);        // ����� ��� ������ ������� ���
	StopTimer1();                            // ���������� ������
} //Dimmer


void Dimmer::UpdateItemValue(int itemUpValue, int itemDownValue)
{
	_itemUpValue = itemUpValue;
	_itemDownValue = itemDownValue;
}

//----------------------����������� ����������--------------------------
void TimerInterrupt() // ���������� ������� ����������� ������ 40 ���
{
	_tic++;                       // �������

	if (_tic >255- _itemUpValue) 	    // ���� ������� ����� �������� ���
	{
		_itemUp->UpdateValue(1);
	}
	if(_tic>255- _itemDownValue)
	{
		_itemDown->UpdateValue(1);
	}
}

void DetectUp()	 // ��������� �������� ���������� �� ����������� ���� �����
{
	_tic = 0;                                 // �������� �������
	ResumeTimer1();
	attachInterrupt(0, DetectDown, RISING);  // ������������� ����������
}


void DetectDown() // ��������� �������� ���������� �� ����������� ���� ������
{
	_tic = 0;                                 // �������� �������
	StopTimer1();

	_itemUp->UpdateValue(0);  // �������� ���
	_itemDown->UpdateValue(0);  // �������� ���

	attachInterrupt(0, DetectUp, FALLING);   // ������������� ����������
}
//----------------------����������� ����������--------------------------
// default destructor
Dimmer::~Dimmer()
{
} //~Dimmer
