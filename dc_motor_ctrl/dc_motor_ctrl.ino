//clock set to 8MHz
int gate_mos1 = 0; //pwm
int speed_adj = A3; //0~255

int pwm;

void setup() 
{
  TCCR0A = 2 << COM0A0 | 2 << COM0B0 | 3 << WGM00;
  TCCR0B = 0 << WGM02 | 2 << CS00;
  TCCR1 = 0 << PWM1A | 0 << COM1A0 | 1 << CS10;
  GTCCR = 1 << PWM1B | 2 << COM1B0;
  
  pinMode(gate_mos1, OUTPUT);
  pinMode(speed_adj, INPUT);
 
  digitalWrite(gate_mos1, LOW);
  pwm = 0;
}

void loop()
{
  readpin();
  writepin(pwm);
  
}

void readpin()
{
  pwm = analogRead(speed_adj);
  pwm = map(pwm, 1023, 0, 255, 0);
}



void writepin(int num)
{
  analogWrite(gate_mos1, num);
}
