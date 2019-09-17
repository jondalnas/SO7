const int motor1A = 10;
const int motor2A = 11;
const int motor1B = 6;
const int motor2B = 5;

void setup() {
  pinMode(motor1A, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2B, OUTPUT);
 
  
}

void loop() {
  forward();
  delay(3000);
  back();
  delay(2000);
  stop();
  delay(2000);

}

void forward() {
  digitalWrite(motor1A,HIGH);
  digitalWrite(motor2A,LOW);
  digitalWrite(motor1B,HIGH);
  digitalWrite(motor2B,LOW);
  analogWrite(motor1A,200);
  analogWrite(motor1B,200);
  
}
void back() {
  digitalWrite(motor1A,LOW);
  digitalWrite(motor2A,HIGH);
  digitalWrite(motor1B,LOW);
  digitalWrite(motor2B,HIGH);
  analogWrite(motor2A,200);
  analogWrite(motor2B,200);
  
}

void drejHoejre() {
  digitalWrite(motor1A,HIGH);
  digitalWrite(motor1B,HIGH);
  analogWrite(motor1A,75);
  analogWrite(motor1B,200);
}

void stop() {
  digitalWrite(motor1A,LOW);
  digitalWrite(motor1B,LOW);
  analogWrite(motor1A,0);
  analogWrite(motor1B,0);
}
