/*
* MenuBoolItem.h
*
* Created: 01.12.2018 21:52:52
* Author: koval
*/
#include <LiquidCrystal_I2C.h>
#include "IMenuItem.h"

#ifndef __MENUBOOLITEM_H__
#define __MENUBOOLITEM_H__


class MenuBoolItem : public IMenuItem
{
	//variables
	public:
	protected:
	private:
	char* _name;
	bool* _changeValue;
	IMenuItem* _parent;
	LiquidCrystal_I2C* _lcd;

	//functions
	public:
	MenuBoolItem(char*, bool*, IMenuItem*, LiquidCrystal_I2C*);
	~MenuBoolItem();
	void GoUp();
	void GoDown();
	IMenuItem* GoChoice();
	char* GetName();
	void Begin();
	void GoMain();
	protected:
	private:
	MenuBoolItem( const MenuBoolItem &c );
	MenuBoolItem& operator=( const MenuBoolItem &c );

}; //MenuBoolItem

#endif //__MENUBOOLITEM_H__
