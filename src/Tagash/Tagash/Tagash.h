#ifndef TAGASH_PLATFORM_H
#define TAGASH_PLATFORM_H

#include <Arduino.h>
#include <Servo.h>
#include "../../Generic/GenericPlatform/GenericPlatform.h"
#include "../../Generic/ServoScanner/ServoScanner.h"

class TagashPlatform {
private:
    GenericPlatform& genericPlatform;
    Motor motor;

public:
    TagashPlatform(
        GenericPlatform& basePlatform,
        uint8_t EN,
        uint8_t IN1,
        uint8_t IN2
    );

    void begin();
    void openBridge();

    GenericPlatform& getGenericPlatform();
};

#endif
