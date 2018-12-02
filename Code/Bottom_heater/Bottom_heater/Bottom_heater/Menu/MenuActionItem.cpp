/*
* MenuBackItem.cpp
*
* Created: 01.12.2018 22:00:41
* Author: koval
*/

#include "MenuActionItem.h"

// default constructor
MenuActionItem::MenuActionItem(char* name,IMenuItem* parent, MenuAction action)
{
	_name = name;
	_parent = parent;
	_action = action;
} //MenuBackItem

// default destructor
MenuActionItem::~MenuActionItem()
{
} //~MenuBackItem

void MenuActionItem::GoUp(){}

void MenuActionItem::GoDown(){}

IMenuItem* MenuActionItem::GoChoice()
{
	return _parent;
}

char* MenuActionItem::GetName()
{
	return _name;
}

void MenuActionItem::Begin()
{
	_action();
}

void MenuActionItem::GoMain(){}
