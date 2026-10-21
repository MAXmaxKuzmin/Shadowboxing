#ifndef NAGMASH_PLATFORM_H
#define NAGMASH_PLATFORM_H

#include <Arduino.h>
#include "../../Generic/GenericPlatform/GenericPlatform.h"
#include "../../Generic/ServoScanner/ServoScanner.h"
#include "../MP3/MP3.h"

class NagmashPlatform {
private:
    GenericPlatform& genericPlatform;
    ServoScanner servoScanner;
    MP3 mp3Player;

public:
    NagmashPlatform(
        GenericPlatform& basePlatform,
        uint8_t mp3TXPin,
        uint8_t mp3RXPin,
        uint8_t servoPin
    );

    void begin();
    void bomb();
    void mp3Play();
    void mp3Stop();
    GenericPlatform& getGenericPlatform();
    ServoScanner& getServoScanner();
};

#endif
