#ifndef ENEMY_DETECTOR_H
#define ENEMY_DETECTOR_H

#include <Arduino.h>

class EnemyDetector {
private:
    uint8_t ldrPin;
    uint16_t threshold;
    uint16_t lastReading;

public:
    EnemyDetector(uint8_t pin, uint16_t detectionThreshold);

    void begin();
    bool detected();
    uint16_t readLight();
    uint16_t getLastReading() const;
};

#endif
