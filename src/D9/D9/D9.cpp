#include "D9.h"

D9Platform::D9Platform(
    GenericPlatform& basePlatform,
    uint8_t ldrPin,
    uint16_t laserThreshold,
    uint8_t servoPin
)
    : genericPlatform(basePlatform),
      enemyDetector(ldrPin, laserThreshold),
      servoScanner(servoPin),
      threatMessageSent(false) {}

void D9Platform::begin() {
    genericPlatform.begin();
    enemyDetector.begin();
    servoScanner.begin();
}

void D9Platform::findEnemy() {
    while (!threatMessageSent) {
        servoScanner.update();
        if (enemyDetector.detected()) {
            genericPlatform.sendMessage("HAMAL", "THREAT", D9Platform::genericPlatform.totalDistance(), servoScanner.getAngle());
            servoScanner.stop();
            threatMessageSent = true;
        }
    }
}

GenericPlatform& D9Platform::getGenericPlatform() {
    return genericPlatform;
}
