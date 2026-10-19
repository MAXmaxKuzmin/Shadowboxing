#include "SoundModule.h"

SoundModule::SoundModule(uint8_t micPin, uint8_t thresholdValue)
    : micPin(micPin),
      threshold(thresholdValue) {}

void SoundModule::begin() {
    pinMode(micPin, INPUT);
}

bool SoundModule::checkForSound() {
    const unsigned long windowMs = 50;
    unsigned long startTime = millis();

    int minValue = 1023;
    int maxValue = 0;

    while (millis() - startTime < windowMs) {
        int value = analogRead(micPin);

        if (value < minValue) minValue = value;
        if (value > maxValue) maxValue = value;
    }

    int soundLevel = maxValue - minValue;

    bool soundDetected = soundLevel >= threshold;

    if (soundDetected) {
        return true;
    }
    return false;
}
