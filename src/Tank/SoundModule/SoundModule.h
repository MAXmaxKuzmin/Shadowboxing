

#ifndef SOUND_MODULE_H
#define SOUND_MODULE_H

#include <Arduino.h>

class SoundModule {
private:
  uint8_t micPin;
  uint8_t threshold;
  bool soundDetected;
  bool soundMessageSent;

public:
  SoundModule(uint8_t micPin, uint8_t thresholdValue);
  void begin();
  bool checkForSound();

};

#endif
