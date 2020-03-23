/*
* Menu.cpp
*
* Created: 01.12.2018 21:38:14
* Author: koval
*/
#include "Menu.h"

// default constructor
Menu::Menu(IMenuItem* item)
{
	_currentItem = item;
} //Menu

// default destructor
Menu::~Menu()
{
} //~Menu

void Menu::GoUp()
{
	_currentItem->GoUp();
}

void Menu::GoDown()
{
	_currentItem->GoDown();
}

void Menu::GoChoice()
{
	_currentItem = _currentItem->GoChoice();
	Begin();
}

void Menu::Begin()
{
	_currentItem->Begin();
}

void Menu::GoMain()
{
	_currentItem->GoMain();
}
