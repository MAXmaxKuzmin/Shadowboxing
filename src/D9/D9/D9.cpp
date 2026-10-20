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
            genericPlatform.sendMessage("TNK", "THREAT", D9Platform::genericPlatform.totalDistance(), servoScanner.getAngle());
            servoScanner.stop();
            threatMessageSent = true;
        }
    }
}

void D9Platform::tow() {
    servoScanner.moveToAngle(90);
}

GenericPlatform& D9Platform::getGenericPlatform() {
    return genericPlatform;
}
