#include "SoftwareSerial.h"

#define SENSORLEFT A0  
#define SENSORMID A1
#define SENSORRIGHT A2
#define motor1A 10
#define motor2A 11
#define motor1B 6
#define motor2B 5
#define RX 3
#define TX 2
int count = 0;
int rightOn = 245;
int leftOn = 255;
int off = 0;
float mid;
float right;
float left;
float safety;
bool autoMode;
bool spin;
int forward;
int side;
bool shoot;

SoftwareSerial bluetooth(TX, RX);

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode(SENSORLEFT, INPUT);
  pinMode(SENSORMID, INPUT);
  pinMode(SENSORRIGHT, INPUT);
  pinMode(motor1A, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2B, OUTPUT);
}


void leftForward(int leftOn) {
  analogWrite(motor1A, off);
  analogWrite(motor2A, leftOn);
}

void rightForward(int rightOn) {
  analogWrite(motor1B, rightOn);
  analogWrite(motor2B, off);
 
}

void rightBack(int rightOn) {
  analogWrite(motor1B, off);
  analogWrite(motor2B, rightOn);
 
}

void leftBack(int leftOn) {
  analogWrite(motor1A, leftOn);
  analogWrite(motor2A, off);
 
}

void leftOff() {
  analogWrite(motor1A, off);
  analogWrite(motor2A, off);
}


void rightOff() {
  analogWrite(motor1B, off);
  analogWrite(motor2B, off);
}

void sharpRight(int rightOn, int leftOn) {
  rightBack(rightOn);
  leftForward(leftOn);
}

void sharpLeft(int rightOn, int leftOn) {
  leftBack(leftOn);
  rightForward(rightOn);
}

void driveStraight(int rightOn, int leftOn) {
  rightForward(rightOn);
  leftForward(leftOn);
}

void softLeft(int rightOn) {
  rightForward(rightOn);
  leftOff();
}

void softRight(int leftOn) {
  leftForward(leftOn);
  rightOff();
}

void back(int rightOn, int leftOn) {
  rightBack(rightOn);
  leftBack(leftOn);
}

void standStill() {
  rightOff();
  leftOff();
}

//xxxxxxxx
// |||||||
// ||||||Shoot
// |||||Right
// ||||Left
// |||Backward
// ||Forward
// |Spinn to win
// Auto

void loop() {
  Serial.println(autoMode);
  if (bluetooth.available()) {
    byte data = bluetooth.read();
    
    autoMode = ((data >> 6) & 1) == 1;
    shoot = ((data >> 0) & 1) == 1;
    spin = ((data >> 5) & 1) == 1;
    forward = ((data >> 4) & 1) - ((data >> 3) & 1);
    side = ((data >> 2) & 1) - ((data >> 1) & 1);
    Serial.println(side);
    for (auto i = 0u; i < 8; i++) Serial.print((int) ((data >> (7 - i)) & 1));
    Serial.println();
  }
  
  if (autoMode) {
    mid = (mid + (analogRead(SENSORMID) > 400)) / 2;
    left = (left + (analogRead(SENSORLEFT) > 400)) / 2;
    right = (right + (analogRead(SENSORRIGHT) > 400)) / 2;
    boolean midHigh = mid > 0.9;
    boolean leftHigh = left > 0.9;
    boolean rightHigh = right > 0.9;
    safety = (abs(0.5 - mid) + abs(0.5 - left) + abs(0.5 - right)) * (2.0/3.0);
    
    /*Serial.print(((analogRead(SENSORLEFT) > 400) ? "H" : "S"));
    Serial.print(((analogRead(SENSORMID) > 400) ? "H" : "S"));
    Serial.print(((analogRead(SENSORRIGHT) > 400) ? "H" : "S"));
    Serial.print(", Left: ");
    Serial.print(analogRead(SENSORLEFT));
    Serial.print(", Mid: ");
    Serial.print(analogRead(SENSORMID));
    Serial.print(", Right: ");
    Serial.println(analogRead(SENSORRIGHT));*/
  
    //Serial.println(safety);
    
    if (!rightHigh && leftHigh) {
      sharpRight(rightOn*safety, leftOn*safety);
    } else if (!leftHigh && rightHigh) {
      sharpLeft(rightOn*safety, leftOn*safety);
    } else if ((!rightHigh && !leftHigh && !midHigh) || ((rightHigh && leftHigh && !midHigh))) {
      driveStraight(rightOn*safety, leftOn*safety);
    } else if (!leftHigh && rightHigh && midHigh) {
      softLeft(leftOn*safety);
    } else if (leftHigh && !rightHigh && midHigh) {
      softRight(rightOn*safety);
    }
    //driveStraight();
  } else {
    if (forward == 1) {
      if (side == 1) {
        softLeft(rightOn);
      } else if (side == -1) {
        softRight(leftOn);
      } else {
        driveStraight(leftOn, rightOn);
      }
    } else if (forward == -1) {
        back(rightOn, leftOn);
    } else {
      if (side == 1) {
        sharpLeft(rightOn, leftOn);
      } else if (side == -1) {
        sharpRight(rightOn, leftOn);
      } else {
        standStill();
      }
    }
  }
}
