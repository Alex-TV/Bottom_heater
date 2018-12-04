/*
* EepromExtension.h
*
* Created: 02.12.2018 19:26:49
* Author: koval
*/


#ifndef __EEPROMEXTENSION_H__
#define __EEPROMEXTENSION_H__


class EepromExtension
{
	//variables
	public:
	protected:
	private:

	//functions
	public:
	EepromExtension();
	~EepromExtension();
	uint8_t Read(int);
	void Write(int, uint8_t);
	void Update(int, uint8_t);
	float FloatRead(int);
	void FloatWrite(int, float);
	unsigned long ULongRead(int);
	void ULongWrite(int, unsigned long);
	long LongRead(int);
	void LongWrite(int, long);
	unsigned int UIntRead(int);
	void UIntWrite(int, unsigned int);
	int IntRead(int);
	void IntWrite(int, int);
	void Clear();
	protected:
	private:
	EepromExtension( const EepromExtension &c );
	EepromExtension& operator=( const EepromExtension &c );

}; //EepromExtension

#endif //__EEPROMEXTENSION_H__
