/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
#include <CyberLib.h> // шустрая библиотека для таймера
/*End of auto generated code by Atmel studio */
//Beginning of Auto generated function prototypes by Atmel Studio
//End of Auto generated function prototypes by Atmel Studio
#define dimPin 4
#define zeroPin 2

void DetectDown();
void DetectUp();
void TimerInterrupt() ;

volatile int tic, Dimmer;

void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	pinMode(dimPin, OUTPUT);
	digitalWrite(dimPin, 0);
	pinMode(zeroPin, INPUT);                 // настраиваем порт на вход для отслеживания прохождения сигнала через ноль
	attachInterrupt(0, DetectUp, FALLING);  // настроить срабатывание прерывания interrupt0 на pin 2 на низкий уровень

	StartTimer1(TimerInterrupt, 40);        // время для одного разряда ШИМ
	StopTimer1();                            // остановить таймер

	Serial.println("Start");
}

void loop() {
	// put your main code here, to run repeatedly:
	// раскомментировать для ввода числа диммирования чеерез монитор порта (0 - 255)
	if (Serial.available()) {
		Dimmer = Serial.parseInt();
		Serial.println(Dimmer);
	}
	
	// раскомментировать для управления потенциометром (аналоговый А0)
	// Dimmer = map(analogRead(0), 0, 1023, 240, 0);
}

//----------------------ОБРАБОТЧИКИ ПРЕРЫВАНИЙ--------------------------
void TimerInterrupt()
{       // прерывания таймера срабатывают каждые 40 мкс

	tic++;                       // счетчик
	if (tic > Dimmer)            // если настало время включать ток
	digitalWrite(dimPin, 1);   // врубить ток
}

void DetectUp()
{    // обработка внешнего прерывания на пересекание нуля снизу
	
	tic = 0;                                  // обнулить счетчик
	ResumeTimer1();                           // перезапустить таймер
	attachInterrupt(0, DetectDown, RISING);  // перенастроить прерывание
}

void DetectDown()
{  // обработка внешнего прерывания на пересекание нуля сверху
	
	tic = 0;                                  // обнулить счетчик
	StopTimer1();                             // остановить таймер
	digitalWrite(dimPin, 0);                  // вырубить ток
	attachInterrupt(0, DetectUp, FALLING);   // перенастроить прерывание
}
//----------------------ОБРАБОТЧИКИ ПРЕРЫВАНИЙ--------------------------
