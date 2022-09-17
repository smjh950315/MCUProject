//clock set to 16MHz
int gate_mos1 = 0; //

int vol_feedback = A2; //Voltage Feedback
int vol_in_feedback = A3; //Voltage Feedback
int vol_ref = A0;

int Vout;
int Vin;
int Vref; 
int pwm_1; //mos1 ctrl
int pwm_max;

void setup() 
{
  TCCR0A = 2 << COM0A0 | 2 << COM0B0 | 3 << WGM00;
  TCCR0B = 0 << WGM02 | 1 << CS00;
  TCCR1 = 0 << PWM1A | 0 << COM1A0 | 1 << CS10;
  GTCCR = 1 << PWM1B | 2 << COM1B0;
  
  pinMode(gate_mos1, OUTPUT); //
  pinMode(vol_feedback, INPUT); //V1 feedback 
  pinMode(vol_in_feedback, INPUT); //Vin feedback 
  pinMode(vol_ref, INPUT); //5V
  
  digitalWrite(gate_mos1, LOW);
  
  pwm_1 = 0; //V1
  pwm_max = 135;
}
//FIRST10
void loop()
{
  readpin();
  while(Vin < Vref * 0.2 || Vin > Vref * 0.6)
  {
    readpin();
    pwm_1 = 0;
    writepin1(pwm_1);
  }
  readpin();
  if (Vout > Vref * 0.8)
  {
    if (pwm_1 == pwm_max)
    {
      readpin();
    }
    else 
    {
      writepin1(++pwm_1);
      readpin();
    }
  }
  readpin();
  if (Vout < Vref * 0.8)
  {
    if (pwm_1 == 0)
    {
      readpin();
    }
    else 
    {
      writepin1(--pwm_1);
      readpin();
    }
  }
}


void readpin()
{
  Vref = analogRead(vol_ref);
  Vref = map(Vref, 1023, 0, 255, 0);
  Vout = analogRead(vol_feedback);
  Vout = map(Vout, 1023, 0, 255, 0);
  Vin = analogRead(vol_in_feedback);
  Vin = map(Vin, 1023, 0, 255, 0);
}

void writepin1(int num)
{
  pwm_1 = num; //V1
  analogWrite(gate_mos1, pwm_1);
}
