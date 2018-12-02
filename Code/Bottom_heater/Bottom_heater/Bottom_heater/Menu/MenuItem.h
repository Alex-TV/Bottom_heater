/*
* MenuItem.h
*
* Created: 01.12.2018 21:38:35
* Author: koval
*/
#include <LiquidCrystal_I2C.h>
#include "IMenuItem.h"


#ifndef __MENUITEM_H__
#define __MENUITEM_H__


class MenuItem	: public IMenuItem
{
	//variables
	public:
	protected:
	private:
	char* _name;
	IMenuItem** _items;
	LiquidCrystal_I2C* _lcd;
	int _currentIndex;
	int _itemsCount;
	
	//functions
	public:
	MenuItem(char*, IMenuItem**,int, LiquidCrystal_I2C*);
	~MenuItem();
	void GoUp();
	void GoDown();
	IMenuItem* GoChoice();
	void Begin();
	char* GetName();
	void GoMain();
	protected:
	private:
	MenuItem( const MenuItem &c );
	MenuItem& operator=( const MenuItem &c );

}; //MenuItem

#endif //__MENUITEM_H__
