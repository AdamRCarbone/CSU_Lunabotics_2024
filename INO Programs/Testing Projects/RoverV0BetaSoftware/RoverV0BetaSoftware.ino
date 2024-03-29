#include <Stepper.h>
// #include <Wiring.Pi.h>

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper Stepper1(stepsPerRevolution, 3, 4, 5, 6);
Stepper Stepper2(stepsPerRevolution, 9, 10, 11, 12);
Stepper Stepper3(stepsPerRevolution, 13, 14, 15, 16);
Stepper Stepper4(stepsPerRevolution, 17, 18, 19, 20);

int threshold = 5;

int stepCount = 0;         // number of steps the motor has taken
int pin1State;
int channel2Value;
int channel4Value;
int channel2Pin = 7;
int channel4pin = 8;
int channel2Percent;
int channel4Percent;



void setup() {
  // initialize the serial port:
  Serial.begin(9600);
}

int pwmTOpercent(int importPWM)
{
  return map(importPWM, 2000, 1000, -102, 100);
}

void loop() {

  channel2Value = pulseIn(channel2Pin, HIGH);
  channel4Value = pulseIn(channel4pin, HIGH);
  //Serial.println(channel2Value);
  channel2Percent = pwmTOpercent(channel2Value);
  channel4Percent = pwmTOpercent(channel4Value);
  //Serial.println(channel2Percent);

if(channel2Percent > threshold) {
  //speed2 = map(channel2Percent, -100, 100, 2048/128, 2048/4);
  Stepper1.step(2048/16);
  Stepper1.setSpeed(15);
  Stepper2.step(2048/16);
  Stepper2.setSpeed(15);
  Stepper3.step(2048/16);
  Stepper3.setSpeed(15);
  Stepper4.step(2048/16);
  Stepper4.setSpeed(15);
}


}