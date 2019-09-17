#include <Servo.h>

Servo cannonservo;

int angle = 0;

const int in1Pin = 5;
const int in2Pin = 4;

void setup() {
  cannonservo.attach(9);
  Serial.begin(9600);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  Serial.println("Det kører");
}

void loop() {
  cannonservo.write(angle);
  if (Serial.available()) {
    char ch = Serial.read();
    if (ch == '+')  {
      Serial.println("Bip");
      digitalWrite(in1Pin,LOW);
      digitalWrite(in2Pin,HIGH);
    }
    else if (ch == '-') {
      Serial.println("Bap");
      digitalWrite(in1Pin,HIGH);
      digitalWrite(in2Pin,LOW);
    }
    else  {
      Serial.println("Stop");
      digitalWrite(in1Pin,LOW);
      digitalWrite(in2Pin,LOW);
    }
  }
}
