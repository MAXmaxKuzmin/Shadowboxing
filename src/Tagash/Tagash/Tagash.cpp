#include "Tagash.h"

TagashPlatform::TagashPlatform(
    GenericPlatform& basePlatform,
    uint8_t EN,
    uint8_t IN1,
    uint8_t IN2
)
    : genericPlatform(basePlatform),
      motor(EN, IN1, IN2) {}

void TagashPlatform::begin() {
    genericPlatform.begin();
    motor.begin();
}

void TagashPlatform::openBridge() {
    while (!motor.openBridge()) {
        String message = genericPlatform.listen();
        if (message == "STOP") {
            motor.stop();
            genericPlatform.
            break;
        }
        genericPlatform.sendLocationIfDue();
    }

}

GenericPlatform& TagashPlatform::getGenericPlatform() {
    return genericPlatform;
}




