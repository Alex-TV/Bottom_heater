/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
#include <AutoPID.h>
#include <EEPROM.h>
#include "Dimmer/Dimmer.h"
#include "Thermometer/Thermometer.h"
#include "Display/Display16x2.h"
/*End of auto generated code by Atmel studio */
//Beginning of Auto generated function prototypes by Atmel Studio
//End of Auto generated function prototypes by Atmel Studio
#define dimDownPin 4
#define dimUpPin 3
#define zeroPin 2
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

Dimmer* _dimmer;
Thermometer* _thermometer;
Display16x2* _display;
AutoPID* _pidUp;
AutoPID* _pidDown;

double _tempUp = 0;
double _tempDown = 0;
double _setTempUp = 0;
double _setTempDown = 0;
double _outputUpVal = 0;
double _outputDownVal = 0;

void setup() {
	//инициализация димира
	DimmerItem dimmerItems[2]{DimmerItem(dimUpPin),DimmerItem(dimDownPin)};
	int itemValues[2]{0,0};
	_dimmer = new Dimmer(zeroPin,dimmerItems,itemValues);
	//инициализация термометра
	_thermometer = new Thermometer(therPinDO,therPinCS,therPinCLK);
	//инициализация дисплея
	_display = new Display16x2(0x27, 16, 2);
	
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

}

void loop() {
	_tempDown = _thermometer->Read();
	_tempUp = 0;
	
	_pidUp->run();
	_pidDown->run();
	
	int pidUpVal = _pidUp->atSetPoint(1);
	int pidDownVal = _pidDown->atSetPoint(1);
	int itemValues[2]{pidUpVal,pidDownVal};
	_dimmer->UpdateItemValue(itemValues);
	
	_display->ClearEdit(0);
	int powerUp = (int)((float)pidDownVal/(float)OUTPUT_MAX*(float)100);
	_display->PrintLineValues(0,_setTempUp,_tempUp,pidUpVal);
	_display->ClearEdit(1);
	int powerDown = (int)((float)pidDownVal/(float)OUTPUT_MAX*(float)100);
	_display->PrintLineValues(1,_setTempDown,_tempDown,powerDown);
}




