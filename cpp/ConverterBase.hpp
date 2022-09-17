#ifndef CONVERTERBASE_H
#define CONVERTERBASE_H
#include "C:/Users/Administrator/AppData/Local/Arduino15/packages/arduino/hardware/avr/1.8.5/cores/arduino/Arduino.h"
#define NONE -1
namespace Converter {
	//	class AttX5 {
	//	public:
	//#include "C:/Users/Administrator/AppData/Local/Arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/avr/include/avr/iotn85.h"
	//#include "C:/Users/Administrator/AppData/Local/Arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/avr/include/avr/iotnx5.h"
	//		void Set();
	//	};
	//	class AttX4 {
	//	public:
	//#include "C:/Users/Administrator/AppData/Local/Arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/avr/include/avr/iotn84a.h"
	//#include "C:/Users/Administrator/AppData/Local/Arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/avr/include/avr/iotnx4.h"
	//		void Set();
	//	};
	class ConverterBase
	{
	private:
	public:
		int PIN_VOLTAGE_REF;
		int PIN_VOLTAGE_FB;
		int PIN_CURRENT_REF;
		int PIN_CURRENT_FB;
		int PIN_FIXED_REF;

		int V_REF;
		int V_FB;
		int I_REF;
		int I_FB;

		bool OverVoltage;
		bool OverCurrent;

		//FBMode 0=invalid,1=CV,2=CC+CV;
		int FBMode = 0;

		ConverterBase();
		void ReadPin();
		void ReadPin(int custom_ref);
	protected:
		void _SetPinFeedback(int pin_voltage_fb, int pin_current_fb);
		void _SetPinInput(int pin_voltage_ref, int pin_voltage_fb);
		void _SetPinInput(int pin_voltage_ref, int pin_voltage_fb, int pin_current_ref, int pin_current_fb);
	};
	class PWM {
	public:
		bool IsMax;
		bool IsMin;
		int Max;
		int Val;
		int Min;
		int PIN;
		PWM();
		PWM(int pin, int min, int max);
		PWM& operator+=(int value);
		PWM& operator-=(int value);
		void Write();
	};
}
#endif // !DCCONVERTER_H