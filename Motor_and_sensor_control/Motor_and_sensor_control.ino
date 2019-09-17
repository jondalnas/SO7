#define SENSORLEFT A0  
#define SENSORMID A1
#define SENSORRIGHT A2
#define motor1A 10
#define motor2A 11
#define motor1B 6
#define motor2B 5
int count = 0;
int on = 255;
int off = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(SENSORLEFT, INPUT);
  pinMode(SENSORMID, INPUT);
  pinMode(SENSORRIGHT, INPUT);
  pinMode(motor1A, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2B, OUTPUT);
}


void leftForward() {
  analogWrite(motor1A, off);
  analogWrite(motor2A, on);
}

void rightForward() {
  analogWrite(motor1B, on);
  analogWrite(motor2B, off);
 
}

void rightBack() {
  analogWrite(motor1B, off);
  analogWrite(motor2B, on);
 
}

void leftBack() {
  analogWrite(motor1A, on);
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

void sharpRight() {
  rightBack();
  leftForward();
}

void sharpLeft() {
  leftBack();
  rightForward();
}

void driveStraight() {
  rightForward();
  leftForward();
}

void softLeft() {
  rightForward();
  leftOff();
}

void softRight() {
  leftForward();
  rightOff();
}

void back() {
  rightBack();
  leftBack();
}

void standStill() {
  rightOff();
  leftOff();
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean Mid = analogRead(SENSORMID)> 400;
  boolean Right = analogRead(SENSORRIGHT) > 400;
  boolean Left = analogRead(SENSORLEFT) > 400;
  Serial.print(((analogRead(SENSORLEFT) > 400) ? "H" : "S"));
  Serial.print(((analogRead(SENSORMID) > 400) ? "H" : "S"));
  Serial.print(((analogRead(SENSORRIGHT) > 400) ? "H" : "S"));
  Serial.print(", Left: ");
  Serial.print(analogRead(SENSORLEFT));
  Serial.print(", Mid: ");
  Serial.print(analogRead(SENSORMID));
  Serial.print(", Right: ");
  Serial.println(analogRead(SENSORRIGHT));
  
  if (!Right && Left) {
    sharpRight();
  } else if (!Left && Right) {
    sharpLeft();
  } else if ((!Right && !Left && !Mid) || ((Right && Left && !Mid))) {
    driveStraight();
  } else if (!Left && Right && Mid) {
    softLeft();
  } else if (Left && !Right && Mid) {
    softRight();
  }
}
