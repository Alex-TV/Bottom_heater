/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
#include <PID_v1.h>
#include <iarduino_Encoder_tmr.h>
#include <LiquidCrystal_I2C.h>
#include <SimpleTimer.h>
#include "Dimmer/Dimmer.h"
#include "Thermometer/Thermometer.h"
#include "Display/Display16x2.h"
#include "Menu/Menu.h"
#include "Menu/IMenuItem.h"
#include "Menu/MenuItem.h"
#include "Menu/MenuActionItem.h"
#include "Menu/MenuBoolItem.h"
#include "Menu/MenuIntItem.h"
#include "Menu/MenuDoubleItem.h"
#include "Extensions/EepromExtension.h"
#include "Buzzer/Buzzer.h"

/*End of auto generated code by Atmel studio */
//Beginning of Auto generated function prototypes by Atmel Studio
//End of Auto generated function prototypes by Atmel Studio
#define dimDownPin 4
#define dimUpPin 3
#define zeroPin 2
#define encoderAPin 5
#define encoderBPin 6
#define encoderButtonPin 7

#define buzerPin 9

#define therPinDO 10
#define therPinCS 11
#define therPinCLK 12
#define OUTPUT_MIN 0
#define OUTPUT_MAX 255
#define KP 2
#define KI 5
#define KD 1

#define memoryUpTempAdress 0
#define memoryDownTempAdress 2

#define numRowsLcd 2
#define numColsLcd 16
#define menuItems 5

#define maxTemp 450
#define minTemp 0

#define timerInterval 100000
#define timerUpdateTemperatureInterval 1000
#define clickBuzzerInterval 50

void CreateMenuItems();
void UpdateTempVal(double& val, int delta);
void EncoderUpdate();
void DisplayUpdate();
void HeatingUpdate();
void EncoderButtonUpdate();
void TimerHeatingInterrupt();
void SaveSettingsInEeprom();
void ExitMenuClick();
void TimerUpdateTemperature();
void StartMenuClick();
void StopMenuClick();

Dimmer* _dimmer;
Thermometer* _thermometer;
Display16x2* _display;
PID* _pidUp;
PID* _pidDown;
iarduino_Encoder_tmr* _encoder;
LiquidCrystal_I2C* _lcd;
Menu* _menu;
SimpleTimer* _timerHeating;
EepromExtension*   _eeprom;
Buzzer* _buzzer;

double _tempUp=0;
double _tempDown=0;
double _setTempUp=150;
double _setTempDown=25;
double _outputUpVal=0;
double _outputDownVal=0;
bool _heaterOn=false;
bool _menuActive=true;
bool _regulationUp=false;
bool _regulationDown=true;
int _pidOldDownVal=0;
int _timerHeatingId=0;
int _timerUpdateTemperatureId=0;

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
	_encoder = new iarduino_Encoder_tmr(encoderAPin,encoderBPin);
	_encoder->begin();
	pinMode(encoderButtonPin, INPUT);
	//инициализация pid
	_pidUp = new PID(&_tempUp, &_outputUpVal,&_setTempUp, KP, KI, KD, DIRECT);
	_pidUp->SetMode(AUTOMATIC);
	_pidDown = new PID(&_tempDown, &_outputDownVal,&_setTempDown,  2, 5, 1, DIRECT);
	_pidDown->SetMode(AUTOMATIC);
	//утсановленая температура	(должно устанавливатся в настройках)
	_eeprom = new EepromExtension();
	_setTempUp = _eeprom->IntRead(memoryUpTempAdress);
	_setTempDown = _eeprom->IntRead(memoryDownTempAdress);
	//инициализация меню
	CreateMenuItems();
	//инициализация таймера
	_timerHeating = new SimpleTimer();
	_timerHeatingId =_timerHeating->setInterval(timerInterval,TimerHeatingInterrupt);
	_timerUpdateTemperatureId =_timerHeating->setInterval(timerUpdateTemperatureInterval,TimerUpdateTemperature);
	//инициализация бузера
	_buzzer = new Buzzer(buzerPin);
}

void loop()
{
	_timerHeating->run();
	_dimmer->Update();
	_buzzer->Run();
	HeatingUpdate();
	EncoderUpdate();
	EncoderButtonUpdate();
}

void TimerHeatingInterrupt()
{
	_timerHeating->restartTimer(_timerHeatingId);
	
	if(!_heaterOn) return;
	if(!_regulationDown) return;

	if(abs(_setTempDown - _tempDown)<2
	&& _outputDownVal > OUTPUT_MIN
	&& _outputDownVal < OUTPUT_MAX
	&& abs(_pidOldDownVal-_outputDownVal)<5)
	{
		_regulationDown = false;
		_regulationUp = true;
	}
	_pidOldDownVal = _outputDownVal;
}

void TimerUpdateTemperature()
{
	_timerHeating->restartTimer(_timerUpdateTemperatureId);
	_tempDown = _thermometer->Read();
	_tempUp = 0;
	DisplayUpdate();
}

void HeatingUpdate()
{
	if(_heaterOn)
	{
		if(_regulationUp)
		{
			_pidUp-> Compute();
		}
		if(_regulationDown)
		{
			_pidDown->Compute();
		}
		int itemValues[2]{_outputUpVal,_outputDownVal};
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
	int powerUp = (int)((float)_outputUpVal/(float)OUTPUT_MAX*(float)100);
	_display->PrintLineValues(0, _setTempUp, _tempUp, powerUp);
	int powerDown =(int)((float)_outputDownVal/(float)OUTPUT_MAX*(float)100);
	_display->PrintLineValues(1, _setTempDown, _tempDown, powerDown);
}

void EncoderUpdate()
{
	int enc = _encoder->read();
	//листание меню
	if(_menuActive)
	{
		if(enc == encLEFT)
		{
			_menu->GoUp();
		}
		else if(enc == encRIGHT)
		{
			_menu->GoDown();
		}
	}
}

void SaveSettingsInEeprom()
{
	int saveTempUp = _eeprom->IntRead(memoryUpTempAdress);
	int saveTempDown = _eeprom->IntRead(memoryDownTempAdress);
	if(saveTempUp != _setTempUp)
	{
		_eeprom->IntWrite(memoryUpTempAdress,_setTempUp);
	}
	if(saveTempDown != _setTempDown)
	{
		_eeprom->IntWrite(memoryDownTempAdress,_setTempDown);
	}
}

bool _buttonDown = false;

void EncoderButtonUpdate()
{
	if(!digitalRead(encoderButtonPin))
	{
		_buttonDown = true;
		return;
	}
	if(_buttonDown)
	{
		if(_menuActive)
		{
			_menu->GoChoice();
		}
		else
		{
			_menuActive = true;
			_menu->Begin();
		}
		_buttonDown = false;
		_buzzer->BuzzerOn(clickBuzzerInterval);
	}
}

void UpdateTempVal(double& val, int delta)
{
	val = val + delta;
	val = min(val,maxTemp);
	val = max(val,minTemp);
}

void CreateMenuItems()
{
	IMenuItem** parItemMain = new IMenuItem*[5];
	IMenuItem* mainMenu = new MenuItem("BOTTOM HEATER:", parItemMain,5, _lcd);
	//parItemMain[0] = new MenuBoolItem("ON/OFF",&_heaterOn, mainMenu, _lcd);
	parItemMain[0] = new MenuDoubleItem("SET TEMP UP",&_setTempUp,mainMenu, _lcd);
	parItemMain[1] = new MenuDoubleItem("SET TEMP DOWN",&_setTempDown,mainMenu, _lcd);
	parItemMain[2] = new MenuActionItem("<<START", mainMenu,StartMenuClick);
	parItemMain[3] = new MenuActionItem("<<STOP", mainMenu,StopMenuClick);
	parItemMain[4] = new MenuActionItem("<<EXIT", mainMenu,ExitMenuClick);
	_menu = new Menu(mainMenu);
	_menu->Begin();
}

void StopMenuClick()
{
	_heaterOn = false;
	_regulationUp=false;
	_regulationDown=false;
	_outputUpVal=0;
	_outputDownVal=0;
	ExitMenuClick();
}

void StartMenuClick()
{
	_heaterOn = true;
	_regulationUp=false;
	_regulationDown=true;
	_outputUpVal=0;
	_outputDownVal=0;
	ExitMenuClick();
}

void ExitMenuClick()
{
	_menuActive = false;
	_menu->GoChoice();
	_menu->GoMain();
	_lcd->clear();
	SaveSettingsInEeprom();
	
}
