#include "EnemyDetector.h"

EnemyDetector::EnemyDetector(uint8_t pin, uint16_t detectionThreshold)
    : ldrPin(pin), threshold(detectionThreshold), lastReading(0) {}

void EnemyDetector::begin() {
    pinMode(ldrPin, INPUT);
}

bool EnemyDetector::detected() {
    lastReading = analogRead(ldrPin);
    return lastReading < threshold;
}

uint16_t EnemyDetector::readLight() {
    lastReading = analogRead(ldrPin);
    return lastReading;
}

uint16_t EnemyDetector::getLastReading() const {
    return lastReading;
}
