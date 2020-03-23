/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
#include "PID_v1.h"
#include "EncoderTmr.h"
#include "LiquidCrystal_I2C.h"
#include "SimpleTimer.h"
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
#include "Settings.h"

/*End of auto generated code by Atmel studio */
//Beginning of Auto generated function prototypes by Atmel Studio
//End of Auto generated function prototypes by Atmel Studio


void CreateMenuItems();
void UpdateTempVal(double &val, int delta);
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
void CheckTempBeep();
void ExitSoundMenuClick();
void ReadSettingsInEeprom();
void EncoderButtonUp();

Dimmer *_dimmer;
Thermometer *_thermometer;
Display16x2 *_display;
PID *_pidUp;
PID *_pidDown;
iarduino_Encoder_tmr *_encoder;
LiquidCrystal_I2C *_lcd;
Menu *_menu;
SimpleTimer *_timerHeating;
EepromExtension *_eeprom;
Buzzer *_buzzer;
//меню
IMenuItem **_parItemMain;
IMenuItem **_parSoundItemMain;
IMenuItem *_mainMenu;
IMenuItem *_soundSettingMenu;

double _tempUp = 0;
double _tempDown = 0;
double _setTempUp = 0;
double _setTempDown = 0;
double _outputUpVal = 0;
double _outputDownVal = 0;
bool _heaterOn = false;
bool _menuActive = true;
bool _regulationUp = false;
bool _regulationDown = true;
int _pidOldDownVal = 0;
int _timerHeatingId = 0;
int _timerUpdateTemperatureId = 0;
bool _temUpBeepOn = true;
bool _temDownBeepOn = true;
bool _menuClickSound = true;
bool _menuTempSetSound = true;
bool _buttonDown = false;

void setup()
{
	//Serial.begin(9600);
	//инициализация димира
	_dimmer = new Dimmer(new DimmerItem(dimUpPin), new DimmerItem(dimDownPin));
	//инициализация термометра
	_thermometer = new Thermometer(therPinDO, therPinCS, therPinCLK);
	//инициализация дисплея
	_lcd = new LiquidCrystal_I2C(0x27, numColsLcd, numRowsLcd);
	_lcd->begin();
	_lcd->clear();
	_display = new Display16x2(_lcd);
	//инициализация энкодера
	_encoder = new iarduino_Encoder_tmr(encoderAPin, encoderBPin);
	_encoder->begin();
	pinMode(encoderButtonPin, INPUT);
	//инициализация pid
	_pidUp = new PID(&_tempUp, &_outputUpVal, &_setTempUp, KP, KI, KD, DIRECT);
	_pidUp->SetOutputLimits(OUTPUT_MIN, OUTPUT_MAX);
	_pidUp->SetMode(AUTOMATIC);
	_pidDown = new PID(&_tempDown, &_outputDownVal, &_setTempDown, KP, KI, KD, DIRECT);
	_pidDown->SetOutputLimits(OUTPUT_MIN, OUTPUT_MAX);
	_pidDown->SetMode(AUTOMATIC);
	//инициализация меню
	CreateMenuItems();
	//инициализация таймера
	_timerHeating = new SimpleTimer();
	_timerHeatingId = _timerHeating->setInterval(timerInterval, TimerHeatingInterrupt);
	_timerUpdateTemperatureId = _timerHeating->setInterval(timerUpdateTemperatureInterval, TimerUpdateTemperature);
	//инициализация бузера
	_buzzer = new Buzzer(buzerPin);

	//утсановленая температура	(должно устанавливатся в настройках)
	_eeprom = new EepromExtension();
	ReadSettingsInEeprom();
}

void loop()
{
	_timerHeating->run();
	_buzzer->Run();
	EncoderUpdate();
	EncoderButtonUpdate();
}

void TimerHeatingInterrupt()
{
	_timerHeating->restartTimer(_timerHeatingId);

	if (!_heaterOn)
		return;
	if (!_regulationDown)
		return;

	//if (abs(_setTempDown - _tempDown) < 2 && _outputDownVal > OUTPUT_MIN && _outputDownVal < OUTPUT_MAX && abs(_pidOldDownVal - _outputDownVal) < 5)
	//{
	//	_regulationDown = false;
	//	_regulationUp = true;
	//}
	_pidOldDownVal = _outputDownVal;
}

void TimerUpdateTemperature()
{
	_timerHeating->restartTimer(_timerUpdateTemperatureId);
	_tempDown = _thermometer->Read();
	_tempUp = 0;
	HeatingUpdate();
	CheckTempBeep();
	DisplayUpdate();
}

void CheckTempBeep()
{
	if (!_menuTempSetSound)
		return;
	if (_menuActive)
		return;
	if (!_heaterOn)
		return;

	if (_temUpBeepOn && _tempUp >= _setTempUp && _regulationUp)
	{
		_buzzer->BuzzerOn(tempBuzzerInterval);
		_temUpBeepOn = false;
	}
	if (_temDownBeepOn && _tempDown >= _setTempDown && _regulationDown)
	{
		_buzzer->BuzzerOn(tempBuzzerInterval);
		_temDownBeepOn = false;
	}
}

void HeatingUpdate()
{
	if (_heaterOn)
	{
		if (_regulationUp)
		{
			_pidUp->Compute();
		}
		if (_regulationDown)
		{
			_pidDown->Compute();
		}
		_dimmer->UpdateItemValue(_outputUpVal, _outputDownVal);
	}
	else
	{
		_dimmer->UpdateItemValue(0, 0);
	}
}

void DisplayUpdate()
{
	if (_menuActive)
		return;
	int powerUp = (int)((float)_outputUpVal / (float)OUTPUT_MAX * (float)100);
	_display->PrintLineValues(0, _setTempUp, _tempUp, powerUp);
	int powerDown = (int)((float)_outputDownVal / (float)OUTPUT_MAX * (float)100);
	_display->PrintLineValues(1, _setTempDown, _tempDown, powerDown);
}

void EncoderUpdate()
{
	int enc = _encoder->read();
	//листание меню
	if (_menuActive)
	{
		if (enc == encLEFT)
		{
			_menu->GoUp();
		}
		else if (enc == encRIGHT)
		{
			_menu->GoDown();
		}
	}
}

void EncoderButtonUpdate()
{
	if (!digitalRead(encoderButtonPin))
	{
		_buttonDown = true;
		return;
	}
	if (_buttonDown)
	{
		_buttonDown = false;
		EncoderButtonUp();
	}
}

void EncoderButtonUp()
{

	if (_menuActive)
	{
		_menu->GoChoice();
	}
	else
	{
		_menuActive = true;
		_menu->Begin();
	}
	if (_menuClickSound)
	{
		_buzzer->BuzzerOn(clickBuzzerInterval);
	}
}

void ReadSettingsInEeprom()
{
	_setTempUp = _eeprom->IntRead(memoryUpTempAdress);
	_setTempDown = _eeprom->IntRead(memoryDownTempAdress);
	_menuClickSound = _eeprom->Read(memoryClickSoundAdress);
	_menuTempSetSound = _eeprom->Read(memoryTempSetSoundAdress);
}

void SaveSettingsInEeprom()
{
	int saveTempUp = _eeprom->IntRead(memoryUpTempAdress);
	int saveTempDown = _eeprom->IntRead(memoryDownTempAdress);
	int saveMenuClickSound = _eeprom->IntRead(memoryClickSoundAdress);
	int saveMenuTempSetSound = _eeprom->IntRead(memoryTempSetSoundAdress);

	if (saveTempUp != _setTempUp)
	{
		_eeprom->IntWrite(memoryUpTempAdress, _setTempUp);
	}
	if (saveTempDown != _setTempDown)
	{
		_eeprom->IntWrite(memoryDownTempAdress, _setTempDown);
	}
	if (saveMenuClickSound != _menuClickSound)
	{
		_eeprom->Write(memoryClickSoundAdress, _menuClickSound);
	}
	if (saveMenuTempSetSound != _menuTempSetSound)
	{
		_eeprom->Write(memoryTempSetSoundAdress, _menuTempSetSound);
	}
}

void UpdateTempVal(double &val, int delta)
{
	val = val + delta;
	val = min(val, maxTemp);
	val = max(val, minTemp);
}

void CreateMenuItems()
{
	_parItemMain = new IMenuItem *[6];
	_parSoundItemMain = new IMenuItem *[3];
	_mainMenu = new MenuItem("BOTTOM HEATER:", _parItemMain, 6, _lcd);
	_soundSettingMenu = new MenuItem("SOUND SETTING:", _parSoundItemMain, 3, _lcd);

	//parItemMain[0] = new MenuBoolItem("ON/OFF",&_heaterOn, mainMenu, _lcd);
	_parItemMain[0] = new MenuDoubleItem("SET TEMP UP", &_setTempUp, _mainMenu, _lcd);
	_parItemMain[1] = new MenuDoubleItem("SET TEMP DOWN", &_setTempDown, _mainMenu, _lcd);
	_parItemMain[2] = _soundSettingMenu;
	_parItemMain[3] = new MenuActionItem("<<START", _mainMenu, StartMenuClick);
	_parItemMain[4] = new MenuActionItem("<<STOP", _mainMenu, StopMenuClick);
	_parItemMain[5] = new MenuActionItem("<<EXIT", _mainMenu, ExitMenuClick);

	_parSoundItemMain[0] = new MenuBoolItem("CLICK BEEP", &_menuClickSound, _soundSettingMenu, _lcd);
	_parSoundItemMain[1] = new MenuBoolItem("TEMP SET BEEP", &_menuTempSetSound, _soundSettingMenu, _lcd);
	_parSoundItemMain[2] = new MenuActionItem("<<EXIT", _mainMenu, ExitSoundMenuClick);

	_menu = new Menu(_mainMenu);
	_menu->Begin();
}

void StopMenuClick()
{
	_heaterOn = false;
	_regulationUp = false;
	_regulationDown = false;
	_outputUpVal = 0;
	_outputDownVal = 0;
	ExitMenuClick();
}

void StartMenuClick()
{
	_heaterOn = true;
	_regulationUp = false;
	_regulationDown = true;
	_outputUpVal = 0;
	_outputDownVal = 0;
	ExitMenuClick();
}

void ExitSoundMenuClick()
{
	//переход назад в предыдущее меню.
	_menu->GoChoice();
	//сброс индекса в меню насторек звука.
	_soundSettingMenu->GoMain();
}

void ExitMenuClick()
{
	_menuActive = false;
	_temDownBeepOn = true;
	_temUpBeepOn = true;
	//выход в главное меню
	_menu->GoChoice();
	//сброс индекса меню
	_menu->GoMain();
	SaveSettingsInEeprom();
	_lcd->clear();
}
