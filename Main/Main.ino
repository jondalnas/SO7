#include "SoftwareSerial.h"
#include <Servo.h>
Servo CannonServoXY;
Servo CannonServoXZ;
#define SENSORLEFT A0  
#define SENSORMID A1
#define SENSORRIGHT A2
#define motor1A 10
#define motor2A 11
#define motor1B 6
#define motor2B 5
#define RX 3
#define TX 2
#define LIMIT 0.7
int count = 0;
int rightOn = 145;
int leftOn =   155;
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
int AngleXY = 0;                                                                                                                                                                        
int AngleXZ = 20; //Under 20 vibrerer den
const int CPin = 7;

SoftwareSerial bluetooth(TX, RX);

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  CannonServoXY.attach(3);
  CannonServoXZ.attach(9);
  CannonServoXY.write(AngleXY);
  CannonServoXZ.write(AngleXZ);
  pinMode(CPin,OUTPUT);
  pinMode(SENSORLEFT, INPUT);
  pinMode(SENSORMID, INPUT);
  pinMode(SENSORRIGHT, INPUT);
  pinMode(motor1A, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2B, OUTPUT);
}

void shooting() {
  digitalWrite(CPin,HIGH);
  delay(100);
  digitalWrite(CPin,LOW);
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

void spinForVictory(int rightOn, int leftOn) {
  leftForward(leftOn);
  rightBack(rightOn);
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
  if (bluetooth.available()) {
    byte data = bluetooth.read();
    
    autoMode = ((data >> 6) & 1) == 1;
    shoot = ((data >> 0) & 1) == 1;
    spin = ((data >> 5) & 1) == 1;
    forward = ((data >> 4) & 1) - ((data >> 3) & 1);
    side = ((data >> 2) & 1) - ((data >> 1) & 1);
    

    Serial.println(data);
  }

  if (shoot) {
    shooting();
    shoot = false;
  }

  if (spin) {
    spinForVictory(rightOn, leftOn);
    delay (5000);
    standStill();
  }
  
  if (autoMode) {
    mid = (mid * mid + (analogRead(SENSORMID) > 400)) / 2;
    left = (left * left + (analogRead(SENSORLEFT) > 600)) / 2;
    right = (right * right + (analogRead(SENSORRIGHT) > 400)) / 2;
    boolean midHigh = mid > LIMIT;
    boolean leftHigh = left > LIMIT;
    boolean rightHigh = right > LIMIT;
    safety = (abs(0.5 - mid) + abs(0.5 - left) + abs(0.5 - right)) * (2.0/3.0);

    //safety *= safety * safety;

    //Serial.println(safety);
    
    Serial.print(((analogRead(SENSORLEFT) > 600) ? "H" : "S"));
    Serial.print(((analogRead(SENSORMID) > 400) ? "H" : "S"));
    Serial.println(((analogRead(SENSORRIGHT) > 400) ? "H" : "S"));
    Serial.print(", Left: ");
    Serial.print(analogRead(SENSORLEFT));
    /*Serial.print(", Mid: ");
    Serial.print(analogRead(SENSORMID));
    Serial.print(", Right: ");
    Serial.println(analogRead(SENSORRIGHT));*/

    if ((analogRead(SENSORMID) < 400 && analogRead(SENSORLEFT) < 600 && analogRead(SENSORRIGHT) < 400) || ((rightHigh && leftHigh && !midHigh))) {
      driveStraight(rightOn*safety, leftOn*safety);
    } else if (!rightHigh && leftHigh) {
      sharpRight(rightOn*safety, leftOn*safety);
    } else if (!leftHigh && rightHigh) {
      sharpLeft(rightOn*safety, leftOn*safety);
    } else if (!leftHigh && rightHigh && midHigh) {
      softLeft(leftOn*safety);
    } else if (leftHigh && !rightHigh && midHigh) {
      softRight(rightOn*safety);
    } else if (analogRead(SENSORMID) > 400 && analogRead(SENSORRIGHT) > 400 && analogRead(SENSORLEFT) > 600) {
      if (left < 0.5 && right > 0.5) {
        sharpLeft(rightOn, leftOn);
      } else if (right < 0.5 && left > 0.5) {
        sharpRight(rightOn, leftOn);
      }
      
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
