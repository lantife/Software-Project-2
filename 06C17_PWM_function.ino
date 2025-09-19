#define PIN_LED 7
#define PERIOD 1000

int p;
double repeat;

void set_period(int period){
  p=period;
  repeat=5000.0/p;
}

void set_duty(int duty){
  double d=duty/100.0;
  for(int i=0;i<repeat;i++){
    digitalWrite(PIN_LED,0);
    delayMicroseconds(p*d);
    digitalWrite(PIN_LED,1);
    delayMicroseconds(p*(1-d));
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED,OUTPUT);
  set_period(PERIOD);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<100;i+=(1+(repeat<1))){
    set_duty(i);
  }
  for(int i=100;i>0;i-=(1+(repeat<1))){
    set_duty(i);
  }
}