/*
* Display16x2.h
*
* Created: 04.09.2018 12:33:45
* Author: koval
*/

#include <LiquidCrystal_I2C.h>

#ifndef __DISPLAY16X2_H__
#define __DISPLAY16X2_H__


class Display16x2 
{
	//variables
	public:
	protected:
	private:
	LiquidCrystal_I2C*  _lcd;
	//functions
	public:
	Display16x2(LiquidCrystal_I2C*);
	void PrintLineValues(int,int,int, int);
	void PrintEditInt(int);
	void PrintEditBool(bool);
	void ClearEdit(int);
	void Clear();
	~Display16x2();
	protected:
	private:
	Display16x2( const Display16x2 &c );
	Display16x2& operator=( const Display16x2 &c );
}; //Display16x2

#endif //__DISPLAY16X2_H__
