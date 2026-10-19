#ifndef TANK_PLATFORM_H
#define TANK_PLATFORM_H

#include <Arduino.h>
#include <Servo.h>
#include "../../Generic/GenericPlatform/GenericPlatform.h"
#include "../SoundModule/soundModule.h"
#include "../../Generic/ServoScanner/ServoScanner.h"

class TankPlatform {
private:
    GenericPlatform& genericPlatform;
    SoundModule soundModule;
    ServoScanner servoScanner;

public:
    TankPlatform(
        GenericPlatform& basePlatform,
        uint8_t micPin,
        uint8_t threshold,
        uint8_t servoPin
    );

    void begin();
    void shoot(uint8_t angle);

    GenericPlatform& getGenericPlatform();
};

#endif
