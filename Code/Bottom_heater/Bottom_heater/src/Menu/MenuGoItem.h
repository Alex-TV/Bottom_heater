/*
* MenuGoItem.h
*
* Created: 02.12.2018 0:02:29
* Author: koval
*/
#include <LiquidCrystal_I2C.h>
#include "IMenuItem.h"

#ifndef __MENUGOITEM_H__
#define __MENUGOITEM_H__


class MenuGoItem  : public IMenuItem
{
	//variables
	public:
	protected:
	private:
	char* _name;
	IMenuItem* _item;
	LiquidCrystal_I2C* _lcd;
	
	//functions
	public:
	MenuGoItem(char*, IMenuItem*, LiquidCrystal_I2C*);
	~MenuGoItem();
	void GoUp();
	void GoDown();
	IMenuItem* GoChoice();
	void GoMain();
	protected:
	private:
	MenuGoItem( const MenuGoItem &c );
	MenuGoItem& operator=( const MenuGoItem &c );

}; //MenuGoItem

#endif //__MENUGOITEM_H__
