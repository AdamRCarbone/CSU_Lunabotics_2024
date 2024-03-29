int triggerPin = 0;
int reversePinGreen = 5;
int groundPinYellow;
int forwardPinBlue = 3;
int actuatorDirection = 0; 

int diggingMotor = 0;
int diggintMotor1PIN = 6;
int diggintMotor2PIN = 7;
int time = 0;

//green reverse
//yellow ground
//blue forward


float sCurve(float x) {
  // Ensure x is within the range of 0 to 100
  x = constrain(x, 0, 100);
  
  // Normalize x to the range of -1 to 1
  float normalizedX = map(x, 0, 100, -1, 1);
  
  // Calculate the cubic S-curve
  float y = normalizedX * normalizedX * normalizedX;
  
  // Map the result back to the range of 0 to 100
  y = map(y, -1, 1, 0, 100);
  
  return y;
}

int convertToMotorSpeed(int percent)
{
  int returnValue;
  returnValue = map(percent, 0, 100, 100, 80);
  return returnValue;
}

void setup() {
   Serial.begin(9600);
   pinMode (0, INPUT);
   pinMode (3, OUTPUT);
   pinMode (5, OUTPUT);
   pinMode (6, OUTPUT);
   pinMode (7, OUTPUT);
   pinMode(LED_BUILTIN, OUTPUT);
}

int tempPercent = 0;

void loop() {
 actuatorDirection = 0;
 diggingMotor = 1;

    switch(actuatorDirection) {
        case -1:
            digitalWrite(forwardPinBlue, HIGH);
            digitalWrite(reversePinGreen, LOW);
            break;
        case 0:
            digitalWrite(forwardPinBlue, LOW);
            digitalWrite(reversePinGreen, LOW);
            break;
        case 1:
            digitalWrite(reversePinGreen, HIGH);
            digitalWrite(forwardPinBlue, LOW);
            break;
    }

    switch(diggingMotor) {
        case -1:
            analogWrite(diggintMotor1PIN, 2000);
            analogWrite(diggintMotor2PIN, 1000);
            break;
        case 0:
            analogWrite(diggintMotor1PIN, 1500);
            analogWrite(diggintMotor2PIN, 1500);
            break;
        case 1:
            analogWrite(diggintMotor2PIN, convertToMotorSpeed(tempPercent++));
            analogWrite(diggintMotor1PIN, convertToMotorSpeed(tempPercent++));
            Serial.println(convertToMotorSpeed(tempPercent++));
            Serial.println(tempPercent++);
            delay(500);
    }

}
