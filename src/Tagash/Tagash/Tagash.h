#ifndef TAGASH_PLATFORM_H
#define TAGASH_PLATFORM_H

#include <Arduino.h>
#include <Servo.h>
#include "../../Generic/GenericPlatform/GenericPlatform.h"
#include "../../Generic/ServoScanner/ServoScanner.h"

class TagashPlatform {
private:
    GenericPlatform& genericPlatform;
    ServoScanner servoScanner;

public:
    TagashPlatform(
        GenericPlatform& basePlatform,
        uint8_t servoPin
    );

    void begin();
    void openBridge();

    GenericPlatform& getGenericPlatform();
};

#endif
