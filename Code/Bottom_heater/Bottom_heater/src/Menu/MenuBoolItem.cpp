/*
* MenuBoolItem.cpp
*
* Created: 01.12.2018 21:52:52
* Author: koval
*/

#include "MenuBoolItem.h"
// default constructor
MenuBoolItem::MenuBoolItem(char *name, bool *changeValue, IMenuItem *parent, LiquidCrystal_I2C *lcd)
{
	_name = name;
	_changeValue = changeValue;
	_parent = parent;
	_lcd = lcd;
} //MenuBoolItem

// default destructor
MenuBoolItem::~MenuBoolItem()
{
} //~MenuBoolItem

void MenuBoolItem::GoUp()
{
	*_changeValue = !*_changeValue;
	Begin();
}

void MenuBoolItem::GoDown()
{
	GoUp();
}

void MenuBoolItem::Begin()
{
	_lcd->clear();
	_lcd->setCursor(0, 0);
	_lcd->print(_name);
	_lcd->setCursor(0, 1);
	_lcd->print(*_changeValue ? "TRUE" : "FALSE");
}

IMenuItem *MenuBoolItem::GoChoice()
{
	return _parent;
}

char *MenuBoolItem::GetName()
{
	return _name;
}

void MenuBoolItem::GoMain() {}
