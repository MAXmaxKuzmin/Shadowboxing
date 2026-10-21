#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
private:
  uint8_t in1;
  uint8_t in2;
  uint8_t enablePin;

public:
  Motor(uint8_t pin1, uint8_t pin2, uint8_t enable);

  void begin();
  void setSpeed(uint8_t speed);
  bool openBridge();
  void stop();
};

#endif
