#ifndef MP3_H
#define MP3_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

class MP3 {
private:
  SoftwareSerial mySoftwareSerial;
  DFRobotDFPlayerMini myDFPlayer;
  bool initialized;

public:
  MP3(uint8_t txdPin, uint8_t rxdPin);

  void begin();
  void play();
  void stop();
};

#endif
