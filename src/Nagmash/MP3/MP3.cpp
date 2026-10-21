#include "MP3.h"

MP3::MP3(uint8_t txdPin, uint8_t rxdPin)
  : mySoftwareSerial(txdPin, rxdPin),
    initialized(false) {}

void MP3::begin() {
  mySoftwareSerial.begin(9600);

  if (!myDFPlayer.begin(mySoftwareSerial, true, true)) {
    initialized = false;
    return;
  }

  initialized = true;
  myDFPlayer.volume(30);
}

void MP3::play() {
  if (!initialized) return;

  myDFPlayer.loop(1);
}
void MP3::stop() {
  if (!initialized) return;

  mySoftwareSerial.write(
    (uint8_t)0x7E
  );
  mySoftwareSerial.write(
    (uint8_t)0xFF
  );
  mySoftwareSerial.write(
    (uint8_t)0x06
  );
  mySoftwareSerial.write(
    (uint8_t)0x16
  );
  mySoftwareSerial.write(
    (uint8_t)0x00
  );
  mySoftwareSerial.write(
    (uint8_t)0x00
  );
  mySoftwareSerial.write(
    (uint8_t)0x00
  );
  mySoftwareSerial.write(
    (uint8_t)0xEF
  );
}
