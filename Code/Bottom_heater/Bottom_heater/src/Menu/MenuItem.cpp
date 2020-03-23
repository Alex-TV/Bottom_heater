/*
* MenuItem.cpp
*
* Created: 01.12.2018 21:38:35
* Author: koval
*/
#include <Arduino.h>
#include "MenuItem.h"

// default constructor
MenuItem::MenuItem(char *name, IMenuItem **items, int itemsCount, LiquidCrystal_I2C *lcd)
{
	_name = name;
	_items = items;
	_lcd = lcd;
	_itemsCount = itemsCount;
	_currentIndex = 0;
} //MenuItem

// default destructor
MenuItem::~MenuItem()
{
} //~MenuItem

void MenuItem::GoUp()
{
	_currentIndex--;
	if (_currentIndex < 0)
	{
		_currentIndex = _itemsCount - 1;
	}
	//_currentIndex = max(_currentIndex,0);
	Begin();
}

void MenuItem::GoDown()
{
	_currentIndex++;
	if (_currentIndex > _itemsCount - 1)
	{
		_currentIndex = 0;
	}
	//_currentIndex = min(_currentIndex,_itemsCount-1);
	Begin();
}

IMenuItem *MenuItem::GoChoice()
{
	return _items[_currentIndex];
}

void MenuItem::Begin()
{
	_lcd->clear();
	_lcd->setCursor(0, 0);
	_lcd->print(_name);
	_lcd->setCursor(0, 1);
	//_lcd->print("> ");
	//_lcd->setCursor(2,1);
	_lcd->print(_items[_currentIndex]->GetName());
}

char *MenuItem::GetName()
{
	return _name;
}

void MenuItem::GoMain()
{
	_currentIndex = 0;
}
