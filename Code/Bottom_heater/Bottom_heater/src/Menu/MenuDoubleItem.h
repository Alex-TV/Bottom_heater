/*
* MenuDoubleItem.h
*
* Created: 01.12.2018 22:50:51
* Author: koval
*/
#include <LiquidCrystal_I2C.h>
#include "IMenuItem.h"

#ifndef __MENUDOUBLEITEM_H__
#define __MENUDOUBLEITEM_H__

class MenuDoubleItem : public IMenuItem
{
	//variables
public:
protected:
private:
	char *_name;
	double *_changeValue;
	IMenuItem *_parent;
	const LiquidCrystal_I2C *_lcd;

	//functions
public:
	MenuDoubleItem(char *, double *, IMenuItem *, LiquidCrystal_I2C *);
	~MenuDoubleItem();
	void GoUp();
	void GoDown();
	IMenuItem *GoChoice();
	char *GetName();
	void Begin();
	void GoMain();

protected:
private:
	MenuDoubleItem(const MenuDoubleItem &c);
	MenuDoubleItem &operator=(const MenuDoubleItem &c);

}; //MenuDoubleItem

#endif //__MENUDOUBLEITEM_H__
