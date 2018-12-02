/*
* MenuIntItem.cpp
*
* Created: 01.12.2018 21:53:30
* Author: koval
*/
#include "MenuIntItem.h"

// default constructor
MenuIntItem::MenuIntItem(char* name, int* changeValue, IMenuItem* parent, LiquidCrystal_I2C* lcd)
{
	_name = name;
	_changeValue = changeValue;
	_parent = parent;
	_lcd = lcd;
} //MenuIntItem

// default destructor
MenuIntItem::~MenuIntItem()
{
} //~MenuIntItem

void MenuIntItem::GoUp()
{
	*_changeValue = *_changeValue+1;
	Begin();
}

void MenuIntItem::GoDown()
{
	*_changeValue = *_changeValue-1;
	Begin();

}

IMenuItem* MenuIntItem::GoChoice()
{
	return _parent;
}

void  MenuIntItem::Begin()
{
	_lcd->clear();
	_lcd->setCursor(0,0);
	_lcd->print(_name);
	_lcd->setCursor(0,1);
	_lcd->print(*_changeValue);
}
char*  MenuIntItem::GetName()
{
	return _name;
}

void  MenuIntItem::GoMain(){}
