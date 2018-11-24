/*
* Display.cpp
*
* Created: 04.09.2018 12:33:45
* Author: koval
*/
#include <Arduino.h>
#include "Display16x2.h"

// default constructor
Display16x2:: Display16x2(int adress, int col, int row)
{
	_lcd = new LiquidCrystal_I2C(adress, col, row);
	_lcd->begin();
	_lcd->clear();
}

void Display16x2::PrintLineValues(int line, int setTemp, int curTemp, int power)
{
	_lcd->setCursor(1,line);
	_lcd->print(line==0?"U:":"D:");
	_lcd->setCursor(3,line);
	_lcd->print(setTemp);
	_lcd->setCursor(6,line);
	_lcd->print("C-");
	_lcd->setCursor(8,line);
	_lcd->print(curTemp);
	_lcd->setCursor(11,line);
	_lcd->print("C ");
	_lcd->setCursor(13,line);
	_lcd->print(power);
	_lcd->setCursor(15,line);
	_lcd->print("%");
}

void Display16x2::PrintEdit(int line)
{
	_lcd->setCursor(0,line);
	_lcd->print(">");
}

void Display16x2::ClearEdit(int line)
{
	_lcd->setCursor(0,0);
	_lcd->print(" ");
}

// default destructor
Display16x2::~Display16x2()
{
} //~Display
