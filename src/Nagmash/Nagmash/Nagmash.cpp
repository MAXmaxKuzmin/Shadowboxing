#include "Nagmash.h"

// Initializes the software serial connection and identifies this device as the sender.
NagmashPlatform::NagmashPlatform(
    GenericPlatform& basePlatform,
    uint8_t mp3TXPin,
    uint8_t mp3RXPin,
    uint8_t servoPin

)
  : genericPlatform(basePlatform),
    servoScanner(servoPin),
    mp3Player(mp3TXPin, mp3RXPin)
{}

// Starts the LoRa serial link
void NagmashPlatform::begin() {
    mp3Player.begin();
    servoScanner.begin();
    genericPlatform.begin();
}

GenericPlatform& NagmashPlatform::getGenericPlatform() {
    return genericPlatform;
}

void NagmashPlatform::bomb() {
    servoScanner.moveToAngle(90);
}

void NagmashPlatform::mp3Play() {
    mp3Player.play();
}

void NagmashPlatform::mp3Stop() {
    mp3Player.stop();
}
