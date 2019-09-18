#define SENSORLEFT A0
#define SENSORMID A1
#define SENSORRIGHT A2
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(SENSORLEFT,INPUT);
  pinMode(SENSORMID,INPUT);
  pinMode(SENSORRIGHT,INPUT);
}

void turnRigth() {
  
}

void turnLeft() {
  
}

void driveStraight() {
  
}

void ninntyLeft() {
  
}

void ninetyRight() {
  
}


void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Left: ");
  Serial.println(analogRead(SENSORLEFT));
  Serial.print("Mid: ");
  Serial.println(analogRead(SENSORMID));
  Serial.print("Right: ");
  Serial.println(analogRead(SENSORRIGHT));

  if (analogRead(SENSORRIGHT) > 500 && analogRead(SENSORLEFT) < 500) {
    turnRight();
  } else if (analogRead(SENSORLEFT) > 500 && analogRead(SENSORRIGHT) < 500) {
    turnLeft();
  } else if ((analogRead(SESNSORRIGHT) > 500 && analogRead(SENSORLEFT) > 500 && analogRead(SENSORMID) > 500) || ((analogRead(SESNSORRIGHT) < 500 && analogRead(SENSORLEFT) < 500 && analogRead(SENSORMID) > 500)) {
    driveStraight();
  } else if (analogRead(SENSORMID) < 500 && analogRead(SESORLEFT) > 500) {
    ninetyLeft();
  }else if (analogRead(SENSORMID) < 500 && analogRead(SESORRIGHT) > 500) {
    ninetyRight();
  }
  
}
