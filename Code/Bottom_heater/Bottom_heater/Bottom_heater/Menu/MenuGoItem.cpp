/*
* MenuGoItem.cpp
*
* Created: 02.12.2018 0:02:29
* Author: koval
*/
#include "MenuGoItem.h"

// default constructor
MenuGoItem::MenuGoItem(char* name, IMenuItem* item, LiquidCrystal_I2C* lcd)
{
	_name = name;
	_item = item;
	_lcd = lcd;
} //MenuGoItem

// default destructor
MenuGoItem::~MenuGoItem()
{
} //~MenuGoItem

void MenuGoItem::GoUp(){}
void MenuGoItem::GoDown(){}
IMenuItem* MenuGoItem::GoChoice()
{
	return _item;
}
