const int motor1A = 13;
const int motor1B = 12;
const int motor2A = 11;
const int motor2B = 10;
const int sensor = 9;

void setup() {
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(sensor,INPUT);
}

void loop() {
  frem();
  delay(3000);
  drejHoejre();
  delay(2000);
  stop();
  delay(1000);

}

void frem() {
  digitalWrite(motor1A,LOW);
  digitalWrite(motor1B,HIGH);
  digitalWrite(motor2A,LOW);
  digitalWrite(motor2B,HIGH);
  
}

void drejHoejre() {
  digitalWrite(motor1A,LOW);
  digitalWrite(motor1B,HIGH);
  digitalWrite(motor2B,LOW);
  digitalWrite(motor2A,HIGH);
}

void stop() {
  digitalWrite(motor1A,LOW);
  digitalWrite(motor1B,LOW);
  digitalWrite(motor2A,LOW);
  digitalWrite(motor2B,LOW);
}
