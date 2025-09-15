#define PIN_LED 7

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200);
  while(!Serial){
    ;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int toggle=0;
  digitalWrite(PIN_LED,toggle);
  delay(1000);
  for(int i=0;i<11;i++){
    toggle^=1;
    digitalWrite(PIN_LED,toggle);
    delay(100);
  }
  while(1){}
}
