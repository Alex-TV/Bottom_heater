/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
#include <AutoPID.h>
#include <EEPROM.h>
#include <RotaryEncoder.h>
#include <LiquidCrystal_I2C.h>
#include <MyMenu.h>
#include <SimpleTimer.h>
#include "Dimmer/Dimmer.h"
#include "Thermometer/Thermometer.h"
#include "Display/Display16x2.h"
/*End of auto generated code by Atmel studio */
//Beginning of Auto generated function prototypes by Atmel Studio
//End of Auto generated function prototypes by Atmel Studio
#define dimDownPin 4
#define dimUpPin 3
#define zeroPin 2
#define encoderAPin 11
#define encoderBPin 12
#define encoderButtonPin 10

#define therPinDO 5
#define therPinCS 6
#define therPinCLK 7
#define OUTPUT_MIN 0
#define OUTPUT_MAX 255
#define KP .12
#define KI .0003
#define KD 0
#define KD 0

#define memoryUpTempAdress 0
#define memoryDownTempAdress 1

#define numRowsLcd 2
#define numColsLcd 16
#define menuItems 5

#define maxTemp 450
#define minTemp 0

#define timerInterval 100000

void MenuCallback(int);
MItm* CreateMenuItems();
void UpdateTempVal(double& val, int delta);
void EncoderUpdate();
void DisplayUpdate();
void HeatingUpdate();
void EncoderButtonUpdate();
void TimerHeatingInterrupt();
void SaveSettingsInEeprom();

Dimmer* _dimmer;
Thermometer* _thermometer;
Display16x2* _display;
AutoPID* _pidUp;
AutoPID* _pidDown;
RotaryEncoder* _encoder;
LiquidCrystal_I2C* _lcd;
Menu* _menu;
SimpleTimer* _timerHeating;

double _tempUp = 0;
double _tempDown = 0;
double _setTempUp = 0;
double _setTempDown = 0;
double _outputUpVal = 0;
double _outputDownVal = 0;
bool _heaterOn = false;
bool _menuActive = true;
int _curMenuIndex=0;
bool _regulationUp = false;
bool _regulationDown = true;
int _pidUpVal =0;
int _pidDownVal =0;
int _pidOldDownVal =0;
int _timerHeatingId;

void setup() {
	//инициализация димира
	DimmerItem dimmerItems[2]{DimmerItem(dimUpPin),DimmerItem(dimDownPin)};
	int itemValues[2]{0,0};
	_dimmer = new Dimmer(zeroPin,dimmerItems,itemValues);
	//инициализация термометра
	_thermometer = new Thermometer(therPinDO,therPinCS,therPinCLK);
	//инициализация дисплея
	_lcd = new LiquidCrystal_I2C(0x27, numColsLcd, numRowsLcd);
	_lcd->begin();
	_lcd->clear();
	_display = new Display16x2(_lcd);
	//инициализация энкодера
	_encoder = new RotaryEncoder(encoderAPin,encoderBPin,5,6,1000);
	pinMode(encoderButtonPin, INPUT);
	//инициализация pid
	_pidUp = new AutoPID(&_tempUp, &_setTempUp, &_outputUpVal, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);
	// если температура выше 4 градусов ниже или выше заданного значения, OUTPUT будет установлен на мин или макс соответственно
	_pidUp->setBangBang(4);
	//set PID update interval to 4000ms
	_pidUp->setTimeStep(4000);
	
	_pidDown = new AutoPID(&_tempDown, &_setTempDown, &_outputDownVal, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);
	// если температура выше 4 градусов ниже или выше заданного значения, OUTPUT будет установлен на мин или макс соответственно
	_pidDown->setBangBang(4);
	//set PID update interval to 4000ms
	_pidDown->setTimeStep(4000);
	
	//утсановленая температура	(должно устанавливатся в настройках)
	_setTempUp = EEPROM.read(memoryUpTempAdress);
	_setTempDown = EEPROM.read(memoryDownTempAdress);

	//инициализация меню
	MItm items[menuItems] = {
		MItm("SETTINGS",0,0), //этот пункт является заголовком подменю с индексом 0 (то есть главного меню)
		MItm("ON/OFF",1), //пункт главного меню, который при выборе переходит на подменю с индексом 1
		MItm("Set temp in up",2), //с индексом 2
		MItm("Set temp in down",3), //и с индексом 3 соответственно
		MItm(" <<Exit",4) //вот так можно создавать кнопку "Назад"
	};
	_menu = new Menu(items/*CreateMenuItems()*/, menuItems, _lcd, MenuCallback,numRowsLcd, ">");
	_menu->goMain();
	//инициализация таймера
	_timerHeating = new SimpleTimer();
	_timerHeatingId =_timerHeating->setInterval(timerInterval,TimerHeatingInterrupt);
}

void loop()
{
	_timerHeating->run();
	_dimmer->Update();
	HeatingUpdate();
	DisplayUpdate();
	EncoderUpdate();
	EncoderButtonUpdate();
}

void TimerHeatingInterrupt()
{
	_timerHeating->restartTimer(_timerHeatingId);
	if(_heaterOn && _regulationDown)
	{
		if(abs(_pidOldDownVal-_pidDownVal)<10)
		{
			_regulationDown = false;
			_regulationUp = true;
		}
		_pidOldDownVal = _pidDownVal;
	}
}

void HeatingUpdate()
{
	if(_heaterOn)
	{
		_tempDown = _thermometer->Read();
		_tempUp = 0;

		if(_regulationUp)
		{
			_pidUp->run();
			_pidUpVal = _pidUp->atSetPoint(1);
		}
		
		if(_regulationDown)
		{
			_pidDown->run();
			_pidDownVal = _pidDown->atSetPoint(1);
		}

		int itemValues[2]{_pidUpVal,_pidDownVal};
		_dimmer->UpdateItemValue(itemValues);
	}
	else
	{
		int itemValues[2]{0,0};
		_dimmer->UpdateItemValue(itemValues);
	}
}

void DisplayUpdate()
{
	if(_menuActive) return;
	_display->ClearEdit(0);
	int powerUp = (int)((float)_pidUpVal/(float)OUTPUT_MAX*(float)100);
	_display->PrintLineValues(0,_setTempUp,_tempUp,powerUp);
	_display->ClearEdit(1);
	int powerDown = (int)((float)_pidDownVal/(float)OUTPUT_MAX*(float)100);
	_display->PrintLineValues(1,_setTempDown,_tempDown,powerDown);
}

void EncoderUpdate()
{
	int enc = _encoder->readEncoder();

	if(_menuActive)
	{
		if(enc>0)
		{
			_lcd->print("enc up");
			delay(1000);
		}
		if(enc<0)
		{
			_lcd->print("enc down");
			delay(1000);
		}
		return;
		//действие с пунктами меню
		if(_curMenuIndex==1)//включить/выключить нагревателя
		{
			if(enc != 0)
			{
				_heaterOn = !_heaterOn;
			}
			_display->PrintEditBool(_heaterOn);

		}
		else if(_curMenuIndex ==2)//настройка температуры верхнего нагревателя
		{
			UpdateTempVal(_tempUp, enc);
			_display->PrintEditInt(_tempUp);
		}
		else if(_curMenuIndex==3)//настройка температуры нижнего нагревателя
		{
			UpdateTempVal(_tempDown, enc);
			_display->PrintEditInt(_tempUp);
		}
		else if (_curMenuIndex == 4)//выход из меню настроек
		{
			_curMenuIndex=0;
			_menu->goBack();
			_display->Clear();
			_menuActive = false;
			SaveSettingsInEeprom();
		}
		//листание меню
		if(enc > 0)
		{
			_menu->goUp();
		}
		else if(enc<0)
		{
			_menu->goDown();
		}
	}
}

void SaveSettingsInEeprom()
{
	int saveUpPid = EEPROM.read(memoryUpTempAdress);
	int saveDownPid = EEPROM.read(memoryDownTempAdress);
	if(saveUpPid != _pidUpVal)
	{
		EEPROM.write(memoryUpTempAdress,_pidUpVal);
	}
	if(saveDownPid != _pidDownVal)
	{
		EEPROM.write(memoryDownTempAdress,_pidDownVal);
	}
}

void EncoderButtonUpdate()
{
	if(!digitalRead(encoderButtonPin))
	{
		if(_menuActive)
		{
			_menu->goNext();
		}
		else
		{
			_menuActive = true;
		}
	}
}

void UpdateTempVal(double& val, int delta)
{
	val = val + delta;
	val = min(val,maxTemp);
	val = max(val,minTemp);
}

void MenuCallback(int index)
{
	//_curMenuIndex = index;
}

MItm* CreateMenuItems()
{
	MItm items[menuItems] = {
		MItm("SETTINGS",0,0), //этот пункт является заголовком подменю с индексом 0 (то есть главного меню)
		MItm("ON/OFF",1), //пункт главного меню, который при выборе переходит на подменю с индексом 1
		MItm("Set temp in up",2), //с индексом 2
		MItm("Set temp in down",3), //и с индексом 3 соответственно
		MItm(" <<Exit",4) //вот так можно создавать кнопку "Назад"
	};
	return items;
}

