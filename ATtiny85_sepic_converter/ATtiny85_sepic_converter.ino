//clock set to 16MHz
int gate_mos1 = 0; //

int vol_feedback = A1; //Voltage Feedback
int vol_incheck = A2; //Input Voltage Feedback
int vol_adj = A3;

int vol_ref = A0;

int Vin; //if input = 6~30v  /6 = 1~5V =51~255 
int Vout; 
int Vadj; 
int pwm_1; //mos1 ctrl

void setup() 
{
  TCCR0A = 2 << COM0A0 | 2 << COM0B0 | 3 << WGM00;
  TCCR0B = 0 << WGM02 | 1 << CS00;
  TCCR1 = 0 << PWM1A | 0 << COM1A0 | 1 << CS10;
  GTCCR = 1 << PWM1B | 2 << COM1B0;

  pinMode(gate_mos1, OUTPUT); //
  pinMode(vol_feedback, INPUT); //V1 feedback 
  pinMode(vol_incheck, INPUT); //read = vin/6
  pinMode(vol_adj, INPUT); //5V

  digitalWrite(gate_mos1, LOW);
  
  pwm_1 = 0; //V1

}

void loop()
{
  readpin();
  while (Vin < 51)
  {
    pwm_1 = 0;
    writepin1(pwm_1);
    readpin();
    delay(1000);
  }
  
  if (Vout < Vadj)
  {
    if (pwm_1 == 185)
    {
      readpin();
    }
    else 
    {
      writepin1(++pwm_1);
      readpin();
    }
  }
  
  if (Vout > Vadj)
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
  Vadj = analogRead(vol_adj);
  Vadj = map(Vadj, 1023, 0, 255, 0);
  Vout = analogRead(vol_feedback);
  Vout = map(Vout, 1023, 0, 255, 0);
  Vin = analogRead(vol_incheck);
  Vin = map(Vin, 1023, 0, 255, 0);
}

void writepin1(int num)
{
  pwm_1 = num; //V1
  analogWrite(gate_mos1, pwm_1);
}
