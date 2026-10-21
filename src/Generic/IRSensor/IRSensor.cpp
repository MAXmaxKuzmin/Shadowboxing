
#include <Arduino.h>
#include "IRSensor.h"

IRSensor::IRSensor(uint8_t sensorPin, uint16_t thresholdValue) : pin(sensorPin), threshold(thresholdValue) {}

void IRSensor::begin() {
  pinMode(pin, INPUT);
}

bool IRSensor::detectsLine() {
  Serial.print(F("Sensor reading on pin "));
  Serial.print(pin);
  Serial.print(F(": "));
  Serial.println(analogRead(pin));
  return analogRead(pin) > threshold;
}
