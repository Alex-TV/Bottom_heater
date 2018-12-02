/*
* MenuDoubleItem.cpp
*
* Created: 01.12.2018 22:50:51
* Author: koval
*/


#include "MenuDoubleItem.h"

// default constructor
MenuDoubleItem::MenuDoubleItem(char* name, double* changeValue, IMenuItem* parent, LiquidCrystal_I2C* lcd)
{
	_name = name;
	_changeValue = changeValue;
	_parent = parent;
	_lcd = lcd;
} //MenuDoubleItem

// default destructor
MenuDoubleItem::~MenuDoubleItem()
{
} //~MenuDoubleItem

void MenuDoubleItem::GoUp()
{
	*_changeValue = *_changeValue+1;
	Begin();
}

void MenuDoubleItem::GoDown()
{
	*_changeValue = *_changeValue-1;
	Begin();
}

IMenuItem* MenuDoubleItem::GoChoice()
{
	return _parent;
}

void MenuDoubleItem::Begin()
{
	_lcd->clear();
	_lcd->setCursor(0,0);
	_lcd->print(_name);
	_lcd->setCursor(0,1);
	_lcd->print(*_changeValue);
}

char* MenuDoubleItem::GetName()
{
	return _name;
}

void MenuDoubleItem::GoMain(){}
