const int motor1A = 10;
const int motor1B = 11;
const int sensor = 9;
const int rod = 0;

void setup() {
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
 
  
}

void loop() {
  frem();
  delay(3000);
  stop();
  delay(2000);

}

void frem() {
  digitalWrite(motor1A,HIGH);
  digitalWrite(motor1B,HIGH);
<<<<<<< Updated upstream
  analogWrite(motor1A,158);
  analogWrite(motor1B,100);
  
}

void drejHoejre() {
=======
  digitalWrite(motor2B,LOW);
  analogWrite(motor1A,158);
  analogWrite(motor1B,100);
  
}
void back() {
  digitalWrite(motor1A,LOW);
  digitalWrite(motor2A,HIGH);
  digitalWrite(motor1B,LOW);
  digitalWrite(motor2B,HIGH);
  analogWrite(motor2A,158);
  analogWrite(motor2B,100);
  
}

void right() {
  digitalWrite(motor1A,LOW);
  digitalWrite(motor2A,HIGH);
  digitalWrite(motor1B,HIGH);
  digitalWrite(motor2B,LOW);
  analogWrite(motor2A,208);
  analogWrite(motor2B,100);
}

void left() {
>>>>>>> Stashed changes
  digitalWrite(motor1A,HIGH);
  digitalWrite(motor1B,HIGH);
<<<<<<< Updated upstream
  analogWrite(motor1A,75);
  analogWrite(motor1B,200);
=======
  digitalWrite(motor2B,LOW);
  analogWrite(motor2A,100);
  analogWrite(motor2B,208);
>>>>>>> Stashed changes
}

void stop() {
  digitalWrite(motor1A,LOW);
  digitalWrite(motor1B,LOW);
  analogWrite(motor1A,0);
  analogWrite(motor1B,0);
}
