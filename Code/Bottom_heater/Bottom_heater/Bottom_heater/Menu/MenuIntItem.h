/*
* MenuIntItem.h
*
* Created: 01.12.2018 21:53:30
* Author: koval
*/
#include <LiquidCrystal_I2C.h>
#include "IMenuItem.h"

#ifndef __MENUINTITEM_H__
#define __MENUINTITEM_H__


class MenuIntItem : public IMenuItem
{
	//variables
	public:
	protected:
	private:
	char* _name;
	int* _changeValue;
	IMenuItem* _parent;
	LiquidCrystal_I2C* _lcd;
	
	//functions
	public:
	MenuIntItem(char*, int*, IMenuItem*, LiquidCrystal_I2C*);
	~MenuIntItem();
	void GoUp();
	void GoDown();
	IMenuItem* GoChoice();
	void Begin();
	char* GetName();
	void GoMain();
	protected:
	private:
	MenuIntItem( const MenuIntItem &c );
	MenuIntItem& operator=( const MenuIntItem &c );

}; //MenuIntItem

#endif //__MENUINTITEM_H__
