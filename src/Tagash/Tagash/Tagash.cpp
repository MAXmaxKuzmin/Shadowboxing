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
    servoScanner.openBridge();
}

GenericPlatform& TagashPlatform::getGenericPlatform() {
    return genericPlatform;
}
