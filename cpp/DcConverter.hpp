#ifndef DCCONVERTER_H
#define DCCONVERTER_H
#include "ConverterBase.hpp"
namespace Converter {
	class DcConverter : ConverterBase
	{
	private:
	public:
		PWM pwm;
		DcConverter();
		void SetPinOutput(int pin_pwm, int pwm_min, int pwm_max);
		void SetPinFeedback(int pin_voltage_fb, int pin_current_fb);
		void SetPinInput(int pin_voltage_ref, int pin_voltage_fb);
		void SetPinInput(int pin_voltage_ref, int pin_voltage_fb, int pin_current_ref, int pin_current_fb);
		void Launch();
		void Launch(int custom_ref);
	};
	class FourSWDcConverter : ConverterBase
	{
	private:
	public:
		PWM pwm_buck;
		PWM pwm_boost;
		FourSWDcConverter();
		void SetPinFeedback(int pin_voltage_fb, int pin_current_fb);
		void SetPinInput(int pin_voltage_ref, int pin_voltage_fb);
		void SetPinInput(int pin_voltage_ref, int pin_voltage_fb, int pin_current_ref, int pin_current_fb);
		void SetPinBuckOutput(int pin_pwm, int pwm_min, int pwm_max);
		void SetPinBoostOutput(int pin_pwm, int pwm_min, int pwm_max);
		void Launch();
		void Launch(int custom_ref);
	};
}
#endif // !DCCONVERTER_H

