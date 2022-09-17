#include "DcConverter.hpp"
using namespace Converter;

DcConverter::DcConverter() {

}
void DcConverter::SetPinOutput(int pin_pwm, int pwm_min, int pwm_max) {
	pwm = PWM(pin_pwm, pwm_min, pwm_max);
}
void DcConverter::SetPinFeedback(int pin_voltage_fb, int pin_current_fb) {
	_SetPinFeedback(pin_voltage_fb, pin_current_fb);
}
void DcConverter::SetPinInput(int pin_voltage_ref, int pin_voltage_fb) {
	_SetPinInput(pin_voltage_ref, pin_voltage_fb);
}
void DcConverter::SetPinInput(int pin_voltage_ref, int pin_voltage_fb, int pin_current_ref, int pin_current_fb) {
	_SetPinInput(pin_voltage_ref, pin_voltage_fb, pin_current_ref, pin_current_fb);
}
void DcConverter::Launch() {
	Launch(NONE);
}
void DcConverter::Launch(int custom_ref) {
	ReadPin(custom_ref);
	if (OverVoltage || OverCurrent) {
		pwm -= 1;
	}
	else {
		pwm += 1;
	}
}

FourSWDcConverter::FourSWDcConverter() {

}
void FourSWDcConverter::SetPinFeedback(int pin_voltage_fb, int pin_current_fb) {
	_SetPinFeedback(pin_voltage_fb, pin_current_fb);
}
void FourSWDcConverter::SetPinInput(int pin_voltage_ref, int pin_voltage_fb) {
	PIN_VOLTAGE_REF = pin_voltage_ref;
	PIN_VOLTAGE_FB = pin_voltage_fb;
	pinMode(PIN_VOLTAGE_REF, INPUT);
	pinMode(PIN_VOLTAGE_FB, INPUT);
	FBMode = 1;
}
void FourSWDcConverter::SetPinInput(int pin_voltage_ref, int pin_voltage_fb, int pin_current_ref, int pin_current_fb) {
	PIN_VOLTAGE_REF = pin_voltage_ref;
	PIN_VOLTAGE_FB = pin_voltage_fb;
	PIN_CURRENT_REF = pin_current_ref;
	PIN_CURRENT_FB = pin_current_fb;
	pinMode(PIN_VOLTAGE_REF, INPUT);
	pinMode(PIN_VOLTAGE_FB, INPUT);
	pinMode(PIN_CURRENT_REF, INPUT);
	pinMode(PIN_CURRENT_FB, INPUT);
	FBMode = 2;
}
void FourSWDcConverter::SetPinBuckOutput(int pin_pwm, int pwm_min, int pwm_max) {
	pwm_buck = PWM(pin_pwm, pwm_min, pwm_max);
}
void FourSWDcConverter::SetPinBoostOutput(int pin_pwm, int pwm_min, int pwm_max) {
	pwm_boost = PWM(pin_pwm, pwm_min, pwm_max);
}
void FourSWDcConverter::Launch() {
	ReadPin();
	if (OverVoltage || OverCurrent) {
		if (pwm_boost.IsMin) {
			pwm_buck -= 1;
		}
		else {
			pwm_boost -= 1;
		}
	}
	else {
		if (pwm_buck.IsMax) {
			pwm_boost += 1;
		}
		else {
			pwm_buck += 1;
		}
	}
}
void FourSWDcConverter::Launch(int custom_ref) {
	ReadPin(custom_ref);
	if (OverVoltage || OverCurrent) {
		if (pwm_boost.IsMin) {
			pwm_buck -= 1;
		}
		else {
			pwm_boost -= 1;
		}
	}
	else {
		if (pwm_buck.IsMax) {
			pwm_boost += 1;
		}
		else {
			pwm_buck += 1;
		}
	}
}

