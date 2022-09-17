#include "ConverterBase.hpp"

using namespace Converter;
//void AttX5::Set() {
//	TCCR0A = 2 << COM0A0 | 2 << COM0B0 | 3 << WGM00;
//	TCCR0B = 0 << WGM02 | 1 << CS00;
//	TCCR1 = 0 << PWM1A | 0 << COM1A0 | 1 << CS10;
//	GTCCR = 1 << PWM1B | 2 << COM1B0;
//}
//void AttX4::Set() {
//	TCCR0A = 2 << COM0A0 | 2 << COM0B0 | 3 << WGM01;
//	TCCR0B = 0 << WGM02 || 1 << CS00;
//	TCCR1A = 2 << COM1A0 | 2 << COM1B0 | 1 << WGM10;
//	TCCR1B = 1 << CS10 | 1 << WGM12;
//}
ConverterBase::ConverterBase() {

}
void ConverterBase::ReadPin() {
	ReadPin(NONE);
}
void ConverterBase::ReadPin(int custom_ref) {
	if (FBMode > 0) {
		if (custom_ref == NONE) {
			V_REF = analogRead(PIN_VOLTAGE_REF);
		}
		else {
			V_REF = custom_ref;
		}		
		V_FB = analogRead(PIN_VOLTAGE_FB);
		if (V_FB > V_REF) {
			OverVoltage = true;			
		}
		else {
			OverVoltage = false;
		}
	}
	else {
		V_REF = 0;
	}
	if (FBMode == 2) {
		if (custom_ref == NONE) {
			I_REF = analogRead(PIN_CURRENT_REF);
		}
		else {
			I_REF = custom_ref;
		}
		I_FB = analogRead(PIN_CURRENT_FB);
		if (I_FB > I_REF) {
			OverCurrent = true;
		}
		else {
			OverCurrent = false;
		}
	}
	else {
		OverCurrent = false;
	}
}
void ConverterBase::_SetPinFeedback(int pin_voltage_fb, int pin_current_fb) {
	PIN_VOLTAGE_FB = pin_voltage_fb;
	pinMode(PIN_VOLTAGE_FB, INPUT);
	PIN_CURRENT_FB = pin_current_fb;
	pinMode(PIN_CURRENT_FB, INPUT);
}
void ConverterBase::_SetPinInput(int pin_voltage_ref, int pin_voltage_fb) {
	_SetPinInput(pin_voltage_ref, pin_voltage_fb, NONE, NONE);
}
void ConverterBase::_SetPinInput(int pin_voltage_ref, int pin_voltage_fb, int pin_current_ref, int pin_current_fb) {
	PIN_VOLTAGE_REF = pin_voltage_ref;
	PIN_VOLTAGE_FB = pin_voltage_fb;
	pinMode(PIN_VOLTAGE_REF, INPUT);
	pinMode(PIN_VOLTAGE_FB, INPUT);
	if (pin_current_ref != -1 && pin_current_fb != -1) {
		PIN_CURRENT_REF = pin_current_ref;
		PIN_CURRENT_FB = pin_current_fb;
		pinMode(PIN_CURRENT_REF, INPUT);
		pinMode(PIN_CURRENT_FB, INPUT);
		FBMode = 2;
	}
	FBMode = 1;
}

PWM::PWM() {

}
PWM::PWM(int pin, int min, int max) {
	Max = max;
	Min = min;
	Val = 0;
	PIN = pin;
	pinMode(PIN, OUTPUT);
	digitalWrite(PIN, LOW);
}
PWM& PWM::operator+=(int value) {
	if (Val + value >= Max) {
		Val = Max;
		IsMax = true;
	}
	else {
		Val += value;
		IsMax = false;
	}
	Write();
	return *this;
}
PWM& PWM::operator-=(int value) {
	if (Val - value <= Min) {
		Val = Min;
		IsMin = true;
	}
	else {
		Val -= value;
		IsMin = false;
	}
	Write();
	return *this;
}
void PWM::Write() {
	analogWrite(PIN, Val);
}