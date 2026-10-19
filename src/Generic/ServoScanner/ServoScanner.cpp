#include "ServoScanner.h"

ServoScanner::ServoScanner(
    uint8_t pin,
    uint8_t minimumAngle,
    uint8_t maximumAngle,
    uint16_t stepInterval
)
    : servoPin(pin),
      angle(minimumAngle),
      minAngle(minimumAngle),
      maxAngle(maximumAngle),
      direction(1),
      stepIntervalMs(stepInterval),
      lastStepTime(0),
      running(true),
      threatDetected(false) {}

void ServoScanner::begin() {
    servo.attach(servoPin);
    angle = minAngle;
    servo.write(angle);

    lastStepTime = millis();
    running = true;
    threatDetected = false;
}

void ServoScanner::update() {
    if (!running || threatDetected) return;

    unsigned long now = millis();

    if (now - lastStepTime < stepIntervalMs) return;

    lastStepTime = now;

    if (direction > 0) {
        if (angle >= maxAngle) {
            direction = -1;
            angle = maxAngle - 1;
        } else {
            ++angle;
        }
    } else {
        if (angle <= minAngle) {
            direction = 1;
            angle = minAngle + 1;
        } else {
            --angle;
        }
    }

    servo.write(angle);
}

uint8_t ServoScanner::getAngle() const {
    return angle;
}

void ServoScanner::moveToAngle(uint8_t targetAngle) {
    if (targetAngle < minAngle || targetAngle > maxAngle) {
        return; // Target angle is out of bounds
    }

    angle = targetAngle;
    servo.write(angle);
}
