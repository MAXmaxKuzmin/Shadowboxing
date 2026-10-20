#include "Tagash.h"

TagashPlatform::TagashPlatform(
    GenericPlatform& basePlatform,
    uint8_t servoPin
)
    : genericPlatform(basePlatform),
      servoScanner(servoPin) {}

void TagashPlatform::begin() {
    genericPlatform.begin();
    servoScanner.begin();
}

void TagashPlatform::openBridge() {
    servoScanner.moveToAngle(90);
}

GenericPlatform& TagashPlatform::getGenericPlatform() {
    return genericPlatform;
}
