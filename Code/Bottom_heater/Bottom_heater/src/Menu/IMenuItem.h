/* 
* IMenuItem.h
*
* Created: 01.12.2018 22:36:10
* Author: koval
*/


#ifndef __IMENUITEM_H__
#define __IMENUITEM_H__


class IMenuItem
{
//functions
public:
	virtual ~IMenuItem(){}
	virtual	void GoUp() =0;
	virtual	void GoDown()=0;
	virtual	IMenuItem* GoChoice()=0;
	virtual void Begin()=0;
	virtual char* GetName()=0;
	virtual void GoMain()=0;
}; //IMenuItem

#endif //__IMENUITEM_H__
