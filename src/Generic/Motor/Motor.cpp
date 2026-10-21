
#include <Arduino.h>
#include "Motor.h"


bool is_deploying = false;
int deploymentStartTime = 0;

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

bool Motor::openBridge() {

  if (!is_deploying) {
    deploymentStartTime = millis();
    setSpeed(200);
    is_deploying = true;
  }

  if (is_deploying && (millis() - deploymentStartTime >= 10000)) {
    stop();
    is_deploying = false;
    return true; // Return true to indicate that the deployment is complete
  }
  return false; // Return false to indicate that the deployment is not yet complete
}
