/*
* Menu.h
*
* Created: 01.12.2018 21:38:14
* Author: koval
*/
#include <LiquidCrystal_I2C.h>
#include "MenuItem.h"

#ifndef __MENU_H__
#define __MENU_H__


class Menu
{
	//variables
	public:
	protected:
	private:
	IMenuItem* _currentItem;
	//functions
	public:
	Menu(IMenuItem*);
	~Menu();
	void GoUp();
	void GoDown();
	void GoChoice();
	void GoBack();
	void GoMain();
	void Begin();
	protected:
	private:
	Menu( const Menu &c );
	Menu& operator=( const Menu &c );

}; //Menu

#endif //__MENU_H__
