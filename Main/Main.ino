#include "SoftwareSerial.h"
#include <stdlib.h>

#define SENSORLEFT A0  
#define SENSORMID A1
#define SENSORRIGHT A2
#define motor1A 10
#define motor2A 11
#define motor1B 6
#define motor2B 5
#define RX 4
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
float carX;
float carY;
float cannonX;
float cannonY;

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

//xxxxxxxx xxxxxxxx xxxxxxxx
// |||||||  |||||||  |||||
// ||||--|  |--||----||--|
// |||  |     |    |    |
// |||  |     |    |    Cannon Y
// |||  |     |    Cannon X
// |||  |     Car Y
// |||  Car X
// ||Shoot
// |Spinn to win
// Auto
//
// Car X
// xxxx
// ||-|
// | |
// | Mandesa
// Sign

byte curr;
uint32_t fullPackage;
String text = "";
void loop() {
  typedef union {
    uint32_t i;
    float   f;
  }
  packed_t;
  
  if (bluetooth.available()) {
    byte data = bluetooth.read();
    //for (int i = 0; i < 32; i++) Serial.print((((uint32_t) data << ((3 - (curr % 4)) * 8)) >> (31 - i)) & 0b1);
    //Serial.println();
    
    fullPackage |= (uint32_t) data << ((3 - (curr % 4)) * 8);
    
    curr++;
    
    //for (int i = 0; i < 8; i++) Serial.print((data >> (7 - i)) & 0b1);
    //Serial.println((char) data);
    text += (char) data;
    
    if (data == 0) {
      /*for (int i = 0; i < 32; i++) Serial.print((fullPackage >> (31 - i)) & 0b1);
      Serial.println();
      
      autoMode = ((fullPackage >> (6 + 3*8)) & 1) == 1;
      spin = ((fullPackage >> (5 + 3*8)) & 1) == 1;
      shoot = ((fullPackage >> (4 + 3*8)) & 1) == 1;
      
      packed_t carX;
      
      byte carXSign = (fullPackage >> (3 + 3*8)) & 0b1;
      byte carXExponent = (fullPackage >> (1 + 3*8) & 0b11);
      byte carXMandesa = (((fullPackage >> (3*8)) & 0b1) << 2) | ((fullPackage >> (5 + 2*8)) & 0b11);

      carX.i = ((uint32_t) carXSign << 31) | ((uint32_t) carXMandesa << 20) | ((uint32_t) carXExponent << 23) | 0b00111110000000000000000000000000;

      packed_t carY;
      
      byte carYSign = (fullPackage >> (4 + 2*8)) & 0b1;
      byte carYExponent = ((fullPackage >> (2 + 2*8)) & 0b11);
      byte carYMandesa = (((fullPackage >> (2*8)) & 0b11) << 2) | ((fullPackage >> (6 + 1*8)) & 0b1);

      carY.i = ((uint32_t) carYSign << 31) | ((uint32_t) carYMandesa << 20) | ((uint32_t) carYExponent << 23) | 0b00111110000000000000000000000000;

      //Serial.println(carYMandesa);
      for (int i = 0; i < 32; i++) Serial.print((fullPackage >> (31 - i)) & 0b1);
      //Serial.println(carX.f);
      //Serial.println(carY.f);
      
      fullPackage = 0;
      Serial.println();

      curr = 0;
      */

      String carXS = "";
      String carYS = "";

      String cannonXS = "";
      String cannonYS = "";

      byte data;

      uint8_t curr = 0;

      for (int i = 0; i < strlen(text.c_str()); i++) {
        if (text.c_str()[i] == ' ') curr++;
        else {
          if (curr == 0) carXS += (char) text.c_str()[i];
          else if (curr == 1) carYS += (char) text.c_str()[i];
          else if (curr == 2) cannonXS += (char) text.c_str()[i];
          else if (curr == 3) cannonYS += (char) text.c_str()[i];
          else if (curr == 4) data = (byte) text.c_str()[i];
        }
      }

      //Serial.println(carXS + ", " + carYS);
      carX = atof(carXS.c_str());
      carY = atof(carYS.c_str());
      
      cannonX = atof(cannonXS.c_str());
      cannonY = atof(cannonYS.c_str());

      autoMode = ((data >> 6) & 1) == 1;
      spin = ((data >> 5) & 1) == 1;
      shoot = ((data >> 4) & 1) == 1;

      text = "";
    }
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
    float leftWheel = leftOn * (carY + carX) / 2;
    float rightWheel = rightOn * (carY - carX) / 2;

    if (leftWheel >= 0) {
      leftForward(leftWheel);
    } else {
      leftBack(-leftWheel);
    }

    if (rightWheel >= 0) {
      rightForward(rightWheel);
    } else {
      rightBack(-rightWheel);
    }
  }
}
