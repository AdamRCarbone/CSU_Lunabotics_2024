#include <SPI.h>
#include <Wire.h>

/* Define Pins */
// Motor 1 pins
int PUL_1 = 6; // PUL pin
int DIR_1 = 7; // DIR pin
// Motor 2 pins
int PUL_2 = 9;
int DIR_2 = 8;

/* Variables */
int pd = 500; // Pulse delay period 500
//int spd = A0; // Potentiometer
boolean setdir_1 = LOW, setdir_2 = LOW; // Set direction

long last_step_1, last_step_2, currTime;
int step_dur_1=500, step_dur_2=500;
bool on_1 = LOW, on_2 = HIGH;
int right_steps = 0, left_steps = 0;

void setup() {
  pinMode (PUL_1, OUTPUT);
  pinMode (PUL_2, OUTPUT);

  pinMode (DIR_1, OUTPUT);
  pinMode (DIR_2, OUTPUT);
  pinMode (LED_BUILTIN, OUTPUT);
  
  Serial.begin(9600);

  Serial.println("here");

  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  //attachInterrupt(digitalPinToInterrupt(2),  )

}

void loop() {
  //pd = 100;
  //pd = map((analogRead(spd)),0,1023,2000,50);

  currTime = micros();
  delay(100);
  /*
  if (currTime - last_udp_check > 200000)
  {
    if (get_input())
    {
      set_movement_1();
      set_movement_2();
    }
    last_udp_check = currTime;
  }*/

  if (step_dur_1 < 450)
    step1();
  if (step_dur_2 < 450)
    step2();
/*
  digitalWrite(DIR_1, setdir);
  digitalWrite(DIR_2, !setdir);

  digitalWrite(PUL_1, HIGH);
  digitalWrite(PUL_2, HIGH);

  delayMicroseconds(pd);

  digitalWrite(PUL_1, LOW);
  digitalWrite(PUL_2, LOW);

  delayMicroseconds(pd);*/
}

void receiveEvent(int howMany)
{
  Serial.println("here");
  char rightSpeed[3];
  char leftSpeed[3];
  char triState;
  char diggingMotor;
  rightSpeed[0] = Wire.read ();
  rightSpeed[1] = Wire.read ();
  rightSpeed[2] = '\0';
  leftSpeed[0] = Wire.read ();
  leftSpeed[1] = Wire.read ();
  leftSpeed[2] = '\0';
  triState = Wire.read ();
  diggingMotor = Wire.read ();
  Serial.print(rightSpeed);
  Serial.print(leftSpeed);
  Serial.print(triState);
  Serial.println(diggingMotor);
  //Serial.println("Right Motor Speed: %s Left Motor Speed: %s Tristate: %c diggingMotor: %c", rightSpeed, leftSpeed, triState, diggingMotor);
 // set_movement_1 (atoi (rightSpeed)-50);
 // set_movement_2 (atoi (leftSpeed)-50);
}



/*bool get_input()
{
  String s;
  if (Serial.available() > 0)
  {
    s = Serial.readString();
    s.toCharArray(packetBuffer, 5);
    return true;
  }
  return false;
}*/

void set_movement_1(int speed)
{
  if (speed < 0)
    setdir_1 = LOW;
  else
    setdir_1 = HIGH;

  step_dur_1 = map(abs(speed), 0, 50, 500, 75);
  //Serial.println(step_dur_1);
}

void set_movement_2(int speed)
{ 
/*  char val[3]; 
  for (int i = 0; i < 2; i++)
    val[i] = packetBuffer[i+2];
  val[2] = '\0';
  int temp = atoi(val);
  temp -= 50;*/
  if (speed < 0)
    setdir_2 = LOW;
  else
    setdir_2 = HIGH;

  step_dur_2 = map(abs(speed), 0, 50, 500, 75);
}

void step1()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  if (currTime - last_step_1 > step_dur_1)
    halfPulse1();
}

void halfPulse1()
{
  on_1 = !on_1;
  digitalWrite(DIR_1, setdir_1);
  digitalWrite(PUL_1, on_1);
  last_step_1 = currTime;
}

void step2()
{
  if (currTime - last_step_2 > step_dur_2)
    halfPulse2();
}

void halfPulse2()
{
  on_2 = !on_2;
  digitalWrite(DIR_2, setdir_2);
  digitalWrite(PUL_2, on_2);
  last_step_2 = currTime;

}