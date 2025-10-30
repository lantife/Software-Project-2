#include <Servo.h>

// Arduino pin assignment
#define PIN_SERVO 10

// configurable parameters
#define _DUTY_MIN 550 // servo full clock-wise position (0 degree)
#define _DUTY_NEU 1475 // servo neutral position (90 degree)
#define _DUTY_MAX 2400 // servo full counter-clockwise position (180 degree)

#define _TARGET 180
#define _SERVO_SPEED 3 // servo speed limit (unit: degree/second)
#define INTERVAL 20     // servo update interval (unit: msec)

// global variables
double TARGET = 550+(_DUTY_MAX-_DUTY_MIN)*(_TARGET/180.0);
unsigned long last_sampling_time; // unit: msec

Servo myservo;

double duty_change_per_interval; // maximum duty difference per interval
double duty_target;    // Target duty time
double duty_curr;      // Current duty time

int toggle_interval, toggle_interval_cnt;

void setup() {
  // initialize GPIO pins
  myservo.attach(PIN_SERVO); 
  
  duty_target = TARGET;
  duty_curr = _DUTY_MIN;
  myservo.writeMicroseconds(duty_curr);
  
  // initialize serial port
  Serial.begin(57600);

  // convert angular speed into duty change per interval.
  // Next two lines are WRONG. you have to modify.
  duty_change_per_interval = 
    (_DUTY_MAX - _DUTY_MIN) * (_SERVO_SPEED / 180.0) * (INTERVAL / 1000.0);

  // remove 'while(1) { }' lines after modify 
  Serial.print("duty_change_per_interval:");
  Serial.println(duty_change_per_interval);
  
  // initialize last sampling time
  last_sampling_time = 0;
}

void loop() {
  // wait until next sampling time. 
  if (millis() < (last_sampling_time + INTERVAL))
    return;

  // adjust duty_curr toward duty_target by duty_change_per_interval
  duty_curr += duty_change_per_interval;
  if (duty_curr > duty_target)
      duty_curr = duty_target;

  // update servo position
  myservo.writeMicroseconds(duty_curr);

  // output the read value to the serial port
  Serial.print("duty_target:"); Serial.print(duty_target);
  Serial.print(",duty_curr:");   Serial.println(duty_curr);

  // update last sampling time
  last_sampling_time += INTERVAL;
}
