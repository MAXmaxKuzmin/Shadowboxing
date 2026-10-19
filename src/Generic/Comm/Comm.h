
#ifndef COMM_H
#define COMM_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class Comm {
private:
  SoftwareSerial loraSerial;
  String sender;
  bool received;

public:
  Comm(
    uint8_t txdPin,
    uint8_t rxdPin,
    String sender
  );

  void begin();
  String listen();
  void sendMessage(String to, String type, int x, int angle, int counter);
};

#endif
