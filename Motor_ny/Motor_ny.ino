const int motor1A = 10;
const int motor1B = 11;

void setup() {
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
 
}

void loop() {
  frem();
  delay(3000);
  stop();
  delay(10000);

}

void frem() {
  digitalWrite(motor1A,HIGH);
  digitalWrite(motor1B,HIGH);
  analogWrite(motor1A,158);
  analogWrite(motor1B,100);
  
}

void drejHoejre() {
  digitalWrite(motor1A,HIGH);
  digitalWrite(motor1B,HIGH);
  analogWrite(motor1A,208);
  analogWrite(motor1B,100);
}

void stop() {
  digitalWrite(motor1A,LOW);
  digitalWrite(motor1B,LOW);
  analogWrite(motor1A,0);
  analogWrite(motor1B,0);
}
