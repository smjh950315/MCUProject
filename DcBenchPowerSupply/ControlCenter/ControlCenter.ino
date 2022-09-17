//參考電壓 2.5V
int pin_out = 17;

int pwm_ch=0;


void setup() {  
  ledcSetup(pwm_ch, 100 * 1000, 8);
  ledcAttachPin(pin_out, pwm_ch);
}

void loop() {
  ledcWrite(pwm_ch, 100);
}
