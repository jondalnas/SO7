#include <Servo.h>
Servo CannonServoXY;
Servo CannonServoXZ;
int AngleXY = 0;
int AngleXZ = 20; //Under 20 vibrerer den
const int CPin = 2;

void setup() {
  CannonServoXY.attach(9);
  CannonServoXZ.attach(10);
  CannonServoXY.write(AngleXY);
  CannonServoXZ.write(AngleXZ);
  pinMode(CPin,OUTPUT);
}

void Skyd() {
  digitalWrite(CPin,HIGH);
  delay(100);
  digitalWrite(CPin,LOW);
}

void loop() { 
}
