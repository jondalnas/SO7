#include <Servo.h>
Servo cannonservo;
int angle = 0;
const int in1Pin = 5;
const int in2Pin = 4;

void setup() {
  cannonservo.attach(9);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
}

void MedUret() {
  digitalWrite(in1Pin,HIGH);
  digitalWrite(in2Pin,LOW);
}

void ModUret() {
  digitalWrite(in1Pin,LOW);
  digitalWrite(in2Pin,HIGH);
}

void Stop() {
  digitalWrite(in1Pin,LOW);
  digitalWrite(in2Pin,LOW);
}


void loop() {
  cannonservo.write(angle);
  /*if (x = true && y = false && z = false) {
    MedUret(); 
  }
  else if (x = false && y = true && z = false)  {
    ModUret();
  }
  else if (x = false && y = false && z = true)  {
    Stop();
  }*/
}
