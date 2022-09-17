#include "Z:/VSCode/MCUProject/cpp/ConverterBase.cpp"
#include "Z:/VSCode/MCUProject/cpp/DcConverter.cpp"
using namespace Converter;
DcConverter conv1;
DcConverter conv2;
int PIN_VOL_REF=A0;
int PIN_VOL_BT;
int PIN_VOL_IN;

int PIN_5V_FB=A1;
int PIN_12V_FB=A2;

int PIN_5V_PWM=7;
int PIN_12V_PWM=8;

void setup() {
  TCCR0A = 2 << COM0A0 | 2 << COM0B0 | 3 << WGM01;
  TCCR0B = 0 << WGM02 || 1 << CS00;
  TCCR1A = 2 << COM1A0 | 2 << COM1B0 | 1 << WGM10;
  TCCR1B = 1 << CS10 | 1 << WGM12;
  conv1.SetPinInput(PIN_5V_FB,PIN_VOL_REF);
  conv1.SetPinOutput(PIN_5V_PWM,0,180);
}
void loop() {
conv1.Launch();
}
