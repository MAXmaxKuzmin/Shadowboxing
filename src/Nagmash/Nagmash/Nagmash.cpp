#include "Nagmash.h"

// Initializes the software serial connection and identifies this device as the sender.
NagmashPlatform::NagmashPlatform(
    GenericPlatform& basePlatform,
    uint8_t mp3TXPin,
    uint8_t mp3RXPin,
    uint8_t servoPin

)
  : genericPlatform(basePlatform),
    servoScanner(servoPin, 80, 150, 17, 150),
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
    genericPlatform.driveForXseconds(3);
    servoScanner.moveToAngle(50);
    genericPlatform.driveForXseconds(2);
    servoScanner.returnHome();

}

void NagmashPlatform::mp3Play() {
    mp3Player.play();
}

void NagmashPlatform::mp3Stop() {
    Serial.println("Stopping MP3 player");
    mp3Player.stop();
    Serial.println("MP3 player stopped");
}

ServoScanner& NagmashPlatform::getServoScanner() {
    return servoScanner;
}

