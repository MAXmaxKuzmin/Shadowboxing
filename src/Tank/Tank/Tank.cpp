#include "Tank.h"

TankPlatform::TankPlatform(
    GenericPlatform& basePlatform,
    uint8_t micPin,
    uint8_t threshold,
    uint8_t servoPin
)
    : genericPlatform(basePlatform),
    soundModule(micPin, threshold),
      servoScanner(servoPin) {}

void TankPlatform::begin() {
    genericPlatform.begin();
    soundModule.begin();
    servoScanner.begin();
}

void TankPlatform::shoot(uint8_t angle) {
    while (!soundModule.checkForSound()) {
        servoScanner.moveToAngle(angle);
    }
}

GenericPlatform& TankPlatform::getGenericPlatform() {
    return genericPlatform;
}
