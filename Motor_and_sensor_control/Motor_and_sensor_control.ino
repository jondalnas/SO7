#define SENSORLEFT A0  
#define SENSORMID A1
#define SENSORRIGHT A2
#define motor1A 10
#define motor2A 11
#define motor1B 6
#define motor2B 5
int count = 0;


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

void turnRight() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2B, LOW);
  analogWrite(motor2A, 100);
  analogWrite(motor2B, 200); 
}

void turnLeft() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2B, HIGH);
  analogWrite(motor2A, 100);
  analogWrite(motor2B, 200);
}

void driveStraight() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2B, LOW);
  analogWrite(motor1A, 158);
  analogWrite(motor1B, 100);
}

void back() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2B, HIGH);
  analogWrite(motor2A, 158);
  analogWrite(motor2B, 100);
  
}

void ninetyLeft() {
  
}

void ninetyRight() {
  
}

void standStill() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2B, LOW);
  analogWrite(motor2A, 0);
  analogWrite(motor2B, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(((analogRead(SENSORLEFT) > 600) ? "H" : "S"));
  Serial.print(((analogRead(SENSORMID) > 600) ? "H" : "S"));
  Serial.print(((analogRead(SENSORRIGHT) > 600) ? "H" : "S"));
  Serial.print(", Left: ");
  Serial.print(analogRead(SENSORLEFT));
  Serial.print(", Mid: ");
  Serial.print(analogRead(SENSORMID));
  Serial.print(", Right: ");
  Serial.println(analogRead(SENSORRIGHT));
  
  if (analogRead(SENSORRIGHT) < 600 && analogRead(SENSORLEFT) > 600) {
    turnRight();
  } else if (analogRead(SENSORLEFT) < 600 && analogRead(SENSORRIGHT) > 600) {
    turnLeft();
  } else if ((analogRead(SENSORRIGHT) < 600 && analogRead(SENSORLEFT) < 600 && analogRead(SENSORMID) < 600) || ((analogRead(SENSORRIGHT) > 600 && analogRead(SENSORLEFT) > 600 && analogRead(SENSORMID) < 600))) {
    driveStraight();
  } else if (analogRead(SENSORMID) > 600 && analogRead(SENSORLEFT) < 600) {
    ninetyLeft();
  }else if (analogRead(SENSORMID) > 600 && analogRead(SENSORRIGHT) < 600) {
    ninetyRight();
  }
}
