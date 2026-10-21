
#include "MP3.h"

MP3::MP3(uint8_t txdPin, uint8_t rxdPin)
  : mySoftwareSerial(txdPin, rxdPin){}

void MP3::begin() {
  mySoftwareSerial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial, true, true)) {
    return;
  }
  myDFPlayer.volume(30);
}

void MP3::play() {
  myDFPlayer.loop(1);
}

void MP3::stop() {
  myDFPlayer.stop();
}
