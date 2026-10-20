#include "Generic/GenericPlatform/GenericPlatform.h"
#include <Arduino.h>

float Distance = 100000;
unsigned long lastMessageTime = 0;
const unsigned long messageInterval = 10000;

GenericPlatform platform(
  7, 8, 6, //Left motor IN1, IN2, EN
  7, 8, 5, //Right motor IN1, IN2, EN
  A5, A4, //IR sensors, left, right
  9, 10, //Lora TX, RX
  11, 12, //Ultrasonic TRIG, ECHO
  4, //IR receiver
  300, //Threshold
  "NAG" //name
);

void setup() {
  platform.begin();
  Serial.begin(9600);
}


void loop() {
  platform.updateDrive();
  delay(1000);
}
