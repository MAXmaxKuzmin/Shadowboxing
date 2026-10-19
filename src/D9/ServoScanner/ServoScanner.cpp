#include "ServoScanner.h"

ServoScanner::ServoScanner(
    uint8_t pin,
    EnemyDetector& enemyDetector,
    uint8_t minimumAngle,
    uint8_t maximumAngle,
    uint16_t stepInterval
)
    : detector(enemyDetector),
      servoPin(pin),
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

    if (detector.detected()) {
        threatDetected = true;
        running = false;
        return;
    }

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

void ServoScanner::stop() {
    running = false;
}

bool ServoScanner::isRunning() const {
    return running;
}

bool ServoScanner::hasDetectedThreat() const {
    return threatDetected;
}

uint8_t ServoScanner::getAngle() const {
    return angle;
}
