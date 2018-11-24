/*
* DimmerItem.h
*
* Created: 24.11.2018 21:45:58
* Author: koval
*/


#ifndef __DIMMERITEM_H__
#define __DIMMERITEM_H__


class DimmerItem
{
	//variables
	public:
	protected:
	private:
	int _dimPin;
	//functions
	public:
	DimmerItem(int);
	~DimmerItem();
	void UpdateValue(int);
	protected:
	private:
	//DimmerItem( const DimmerItem &c );
	DimmerItem& operator=( const DimmerItem &c );

}; //DimmerItem

#endif //__DIMMERITEM_H__
