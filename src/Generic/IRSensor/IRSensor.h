
#ifndef IR_SENSOR_H
#define IR_SENSOR_H

#include <Arduino.h>

class IRSensor {
private:
  uint8_t pin;
  uint16_t threshold;

public:
  IRSensor(uint8_t sensorPin, uint16_t thresholdValue);

  void begin();
  bool detectsLine();

};

#endif
