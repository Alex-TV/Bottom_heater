/*
* DimmerItem.cpp
*
* Created: 24.11.2018 21:45:58
* Author: koval
*/
#include <Arduino.h>
#include "DimmerItem.h"

// default constructor
DimmerItem::DimmerItem(int dimPin)
{
	_dimPin = dimPin;
	pinMode(_dimPin, OUTPUT);
	digitalWrite(_dimPin, 0);
} //DimmerItem

void DimmerItem::UpdateValue(int dimVal)
{
	digitalWrite(_dimPin, dimVal);
}
// default destructor
DimmerItem::~DimmerItem()
{
} //~DimmerItem
