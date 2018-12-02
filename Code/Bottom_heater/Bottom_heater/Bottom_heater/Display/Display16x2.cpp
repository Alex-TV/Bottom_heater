/*
* Display.cpp
*
* Created: 04.09.2018 12:33:45
* Author: koval
*/
#include <Arduino.h>
#include "Display16x2.h"

// default constructor
Display16x2:: Display16x2(LiquidCrystal_I2C* lcd)
{
	_lcd = lcd;
}

void Display16x2::PrintLineValues(int line, int setTemp, int curTemp, int power)
{
	_lcd->setCursor(0,line);
	_lcd->print(line==0?"U:":"D:");
	String setTempStr = String(setTemp, DEC);
	SetCurCursor(setTempStr.length(),2, 3, line);
	_lcd->print(setTempStr);
	_lcd->setCursor(5,line);
	_lcd->print("C ");
	_lcd->setCursor(7,line);
	_lcd->print("   ");
	String curTempStr = String(curTemp, DEC);
	SetCurCursor(curTempStr.length(),7, 3, line);
	_lcd->print(curTempStr);
	_lcd->setCursor(10,line);
	_lcd->print("C");
	_lcd->setCursor(12,line);
	_lcd->print("   ");
	String powerStr = String(power, DEC);
	SetCurCursor(powerStr.length(),12, 3, line);
	_lcd->print(powerStr);
	_lcd->setCursor(15,line);
	_lcd->print("%");
}

void Display16x2::SetCurCursor(int curLength, int startCursor, int numLength, int line)
{
	_lcd->setCursor(startCursor+ numLength -  curLength,line);
}

void  Display16x2::Clear()
{
	_lcd->clear();
}
// default destructor
Display16x2::~Display16x2()
{
} //~Display


