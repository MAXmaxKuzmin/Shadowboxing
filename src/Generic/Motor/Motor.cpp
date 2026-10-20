
#include <Arduino.h>
#include "Motor.h"

Motor::Motor(uint8_t pin1, uint8_t pin2, uint8_t enable)
  : in1(pin1), in2(pin2), enablePin(enable) {}

void Motor::begin() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  stop();
}

void Motor::setSpeed(uint8_t speed) {
  speed = constrain(speed, 0, 255);

  if (speed > 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  } else if (speed < 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else {
    stop();
    return;
  }

  analogWrite(enablePin, abs(speed));
}

void Motor::stop() {
  analogWrite(enablePin, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}
