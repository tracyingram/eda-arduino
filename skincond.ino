#include <util/delay.h>

//setup defines
//make things as parametric as possible
#define TOPR 20000.0
#define BOTTOMR 20000.0
#define ADCMAX 1023
#define TOPV 0.5
#define ADCREF 5.0
#define SAMPDELAY 125



void setup()
{
  ADCSRA &= ~(0x03); //fast ADC - div8
  //0x07 for fastest div2
  
  digitalWrite(A0, 0);
  pinMode(A0, 0);
  
  Serial.begin(115200);
  
}



void loop()
{
  int raw = analogRead(A0);
  float wheatV = ADCREF * raw/ADCMAX;
  float tmp = wheatV/TOPV + BOTTOMR/(TOPR+BOTTOMR);
  float res = tmp*TOPR/(1-tmp);
  float cond = 1/res;
  cond *= 1000000.0; //micromhos
  //I'm sure this can be simplified, but this should follow wheatstone equations
  //I'm assuming the above takes around 200uS which is small compared to sample rate
  
  
  Serial.println(cond);
  _delay_ms(SAMPDELAY);
  
  
}

