//	Библиотека для работы с энкодерами: http://iarduino.ru/shop/Expansion-payments/enkoder-trema-modul.html
//  Версия: 1.0.1
//  Последнюю версию библиотеки Вы можете скачать по ссылке: http://iarduino.ru/file/297.html
//  Подробное описание функции бибилиотеки доступно по ссылке: http://wiki.iarduino.ru/page/enkoder-trema-modul/
//  Библиотека является собственностью интернет магазина iarduino.ru и может свободно использоваться и распространяться!
//  При публикации устройств или скетчей с использованием данной библиотеки, как целиком, так и её частей,
//  в том числе и в некоммерческих целях, просим Вас опубликовать ссылку: http://iarduino.ru
//  Автор библиотеки: Панькин Павел sajaem@narod.ru
//  Если у Вас возникли технические вопросы, напишите нам: shop@iarduino.ru

#ifndef iarduino_Encoder_tmr_h
#define iarduino_Encoder_tmr_h

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#if defined(__AVR_ATmega32U4__)													//	Если используется плата на базе микроконтроллера ATmega32U4 (Arduino Micro или Arduino Leonardo), то ...
#if !defined(TCCR2A)															//	Если Arduino IDE не знает, что у этих микроконтроллеров есть второй аппаратный таймер, то ...
	#define TCCR2A					(*(uint8_t*)0xB0)							//	Определяем смещение для регистра TCCR2A - регистр выбора режима
	#define COM2A1					7											//	Определяем позицию  в регистре   TCCR2A для старшего бита выбора режима сравнения канала А
	#define COM2A0					6											//	Определяем позицию  в регистре   TCCR2A для младшего бита выбора режима сравнения канала А
	#define COM2B1					5											//	Определяем позицию  в регистре   TCCR2A для старшего бита выбора режима сравнения канала B
	#define COM2B0					4											//	Определяем позицию  в регистре   TCCR2A для младшего бита выбора режима сравнения канала B
	#define WGM21					1											//	Определяем позицию  в регистре   TCCR2A для 1 бита выбора режима работы таймера
	#define WGM20					0											//	Определяем позицию  в регистре   TCCR2A для 0 бита выбора режима работы таймера
	#define TCCR2B					(*(uint8_t*)0xB1)							//	Определяем смещение для регистра TCCR2B - рагистр делителя
	#define FOC2A					7											//	Определяем позицию  в регистре   TCCR2B для бита принудительной установки результата сравнения канала A
	#define FOC2B					6											//	Определяем позицию  в регистре   TCCR2B для бита принудительной установки результата сравнения канала B
	#define WGM22					3											//	Определяем позицию  в регистре   TCCR2B для 2 бита выбора режима работы таймера
	#define CS22					2											//	Определяем позицию  в регистре   TCCR2B для старшего бита выбора источника тактового сигнала таймера
	#define CS21					1											//	Определяем позицию  в регистре   TCCR2B для среднего бита выбора источника тактового сигнала таймера
	#define CS20					0											//	Определяем позицию  в регистре   TCCR2B для младшего бита выбора источника тактового сигнала таймера
	#define TCNT2					(*(uint8_t*)0xB2)							//	Определяем смещение для регистра TCNT2  - счётный регистр
	#define OCR2A					(*(uint8_t*)0xB3)							//	Определяем смещение для регистра OCR2A  - регистр сравнения канала A
	#define OCR2B					(*(uint8_t*)0xB4)							//	Определяем смещение для регистра OCR2B  - регистр сравнения канала B
	#define TIFR2					(*(uint8_t*)0x37)							//	Определяем смещение для регистра TIFR2  - регистр флагов
	#define OCF2B					2											//	Определяем позицию  в регистре   TIFR2  для флага совпадения значения счетного регистра TCNT2 с регистром сравнения OCR2A
	#define OCF2A					1											//	Определяем позицию  в регистре   TIFR2  для флага совпадения значения счетного регистра TCNT2 с регистром сравнения OCR2B
	#define TOV2					0											//	Определяем позицию  в регистре   TIFR2  для флага переполнения счетного регистра TCNT2
	#define TIMSK2					(*(uint8_t*)0x70)							//	Определяем смещение для регистра TIMSK2 - регистр разрешения прерываний
	#define OCIE2B					2											//	Определяем позицию  в регистре   TIMSK2 для бита разрешения прерываний по установке флага OCF2B
	#define OCIE2A					1											//	Определяем позицию  в регистре   TIMSK2 для бита разрешения прерываний по установке флага OCF2A
	#define TOIE2					0											//	Определяем позицию  в регистре   TIMSK2 для бита разрешения прерываний по установке флага TOF2
	#define TIMER2_COMPA_vect_num	13											//	Определяем номер  вектора  для  события установки флага OCF2A
	#define TIMER2_COMPA_vect		_VECTOR(13)									//	Определяем вектор прерываний по событию установки флага OCF2A
	#define TIMER2_COMPB_vect_num	14											//	Определяем номер  вектора  для  события установки флага OCF2B
	#define TIMER2_COMPB_vect		_VECTOR(14)									//	Определяем вектор прерываний по событию установки флага OCF2B
	#define TIMER2_OVF_vect_num		15											//	Определяем номер  вектора  для  события установки флага TOV2
	#define TIMER2_OVF_vect			_VECTOR(15)									//	Определяем вектор прерываний по событию установки флага TOV2
#endif																			//
#endif																			//

#define	encLEFT						-1											//	Константа указывающая, что цвет применяется ко всем светодиодам
#define	encRIGHT					1											//	Константа указывающая, что цвет применяется ко всем светодиодам
	
class iarduino_Encoder_tmr{
	public:							iarduino_Encoder_tmr	(uint8_t, uint8_t);	//	Создание экземпляра класса			(№ вывода, № вывода)
					bool			begin					(void);				//	Инициализация работы с энкодером	(без параметров)
					int8_t			read					(void);				//	Чтение состояния энкодера			(без параметров)
	private:
		volatile	uint8_t			enc_NUM					=	0;				//	Определяем переменную для хранения номера подключённого энкодера
					void			func_TIMER2_SETREG		(uint32_t);			//	Функция конфигурирования таймера
};

class iarduino_Encoder_tmr_VolatileClass{
	public:
		volatile	uint8_t			enc_SUM					=	0;				//	Определяем переменную для хранения количества подключённых энкодеров
		volatile	uint8_t			pin_NUMa[8];								//	Объявляем массив с номерами выводов к которым подключены энкодеры
		volatile	uint8_t			pin_NUMb[8];								//	Объявляем массив с номерами выводов к которым подключены энкодеры
		volatile	uint8_t	*		pin_PRTa[8];								//	Объявляем массив с указателями на адреса входных портов выводов
		volatile	uint8_t	*		pin_PRTb[8];								//	Объявляем массив с указателями на адреса входных портов выводов
		volatile	uint8_t			pin_MSKa[8];								//	Объявляем массив с масками выводов для входных портов выводов
		volatile	uint8_t			pin_MSKb[8];								//	Объявляем массив с масками выводов для входных портов выводов
		volatile	uint8_t			val_BITS[8];								//	Объявляем массив с последними значениями прочитанными с выводов энкодера (abababab)
		volatile	int8_t			i,j;										//	Объявляем переменную для внутренних нужд
};

#endif