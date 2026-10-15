
#ifndef GENERIC_PLATFORM_H
#define GENERIC_PLATFORM_H

#include <Arduino.h>
#include "../TankDrive/TankDrive.h"
#include "../IRSensor/IRSensor.h"
#include "../LineFollower/LineFollower.h"
#include "../Comm/Comm.h"
#include "../Sonic/Sonic.h"
#include "../IRReceiver/IRReceiver.h"

class GenericPlatform {
private:
  TankDrive driveSystem;
  IRSensor leftSensor;
  IRSensor rightSensor;
  LineFollower lineFollower;
  Comm comunication;
  UltrasonicSensor sonic;
  IRReceiver irReceiver;


public:
  GenericPlatform(
    uint8_t  leftIn1, uint8_t  leftIn2, uint8_t  leftEnable,
    uint8_t  rightIn1, uint8_t  rightIn2, uint8_t  rightEnable,
    uint8_t  leftIRPin, uint8_t  rightIRPin,
    uint8_t  commTXD, uint8_t  commRXD,
    uint8_t  sonicTrigPin, uint8_t  sonicEchoPin,
    uint8_t  irReceiverPin,
    uint16_t threshold, String name
  );

  void begin();
  int updateDrive();
  void stopDrive();
  String listen();
  void sendMessage(String to, String type, int x, int y, int angle);
  float checkSonicDistance();
  uint8_t updateIRReceiver();

};

#endif
