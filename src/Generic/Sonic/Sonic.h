
#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include <Arduino.h>

class UltrasonicSensor {
private:
  uint8_t trigPin;
  uint8_t echoPin;

  float lastDistance;

public:
  UltrasonicSensor(uint8_t trigger, uint8_t echo);

  void begin();

  float readDistanceCm();

  float getLastDistance();
};

#endif
