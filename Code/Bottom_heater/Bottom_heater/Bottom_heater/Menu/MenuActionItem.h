/*
* MenuBackItem.h
*
* Created: 01.12.2018 22:00:41
* Author: koval
*/
#include <LiquidCrystal_I2C.h>
#include "IMenuItem.h"

#ifndef __MENUACTIONITEM_H__
#define __MENUACTIONITEM_H__

#ifndef __AVR__
typedef std::function<void(void)> MenuAction;
#else
typedef void (*MenuAction)();
#endif // __AVR__

class MenuActionItem : public IMenuItem
{
	//variables
	public:
	protected:
	private:
	char* _name;
	IMenuItem* _parent;
	MenuAction _action;
	
	//functions
	public:
	MenuActionItem(char*,IMenuItem*, MenuAction );
	~MenuActionItem();
	void GoUp();
	void GoDown();
	IMenuItem* GoChoice();
	char* GetName();
	void Begin();
	void GoMain();
	protected:
	private:
	MenuActionItem( const MenuActionItem &c );
	MenuActionItem& operator=( const MenuActionItem &c );

}; //MenuActionItem

#endif //__MENUACTIONITEM_H__
