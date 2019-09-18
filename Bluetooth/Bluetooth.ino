#include "SoftwareSerial.h"

#define RX 3
#define TX 2
#define test 7

SoftwareSerial bluetooth(TX, RX);

int flag = 0;

void setup() {
  Serial.begin(19200);
  bluetooth.begin(9600);

  pinMode(test, OUTPUT);
}

String acc = "";

void loop() {
  if (bluetooth.available()) {
    char c = bluetooth.read();
    bluetooth.write(c);
    Serial.print(c);
    Serial.print(", ");
    for (auto i = 0u; i < 8; i++) Serial.print((c >> (7 - i)) & 1);
    Serial.println();
  }

  if (Serial.available()) {
    bluetooth.write(Serial.read());
  }
}
