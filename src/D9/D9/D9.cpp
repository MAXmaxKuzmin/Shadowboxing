#include "D9.h"

D9Platform::D9Platform(
    GenericPlatform& basePlatform,
    uint8_t ldrPin,
    uint16_t laserThreshold,
    uint8_t servoPin
)
    : genericPlatform(basePlatform),
      enemyDetector(ldrPin, laserThreshold),
      servoScanner(servoPin, enemyDetector),
      threatMessageSent(false) {}

void D9Platform::begin() {
    genericPlatform.begin();
    enemyDetector.begin();
    servoScanner.begin();

    threatMessageSent = false;
}

void D9Platform::update() {
    if (threatMessageSent) return;

     servoScanner.update();

    if (servoScanner.hasDetectedThreat()) {
        genericPlatform.sendMessage("HAMAL", "THREAT", D9Platform::genericPlatform.totalDistance(), servoScanner.getAngle());

        threatMessageSent = true;
        servoScanner.stop();
    }
}

GenericPlatform& D9Platform::getGenericPlatform() {
    return genericPlatform;
}
