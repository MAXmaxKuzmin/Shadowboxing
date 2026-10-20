#ifndef SERVO_SCANNER_H
#define SERVO_SCANNER_H

#include <Arduino.h>
#include <Servo.h>

class ServoScanner {
private:
    Servo servo;

    uint8_t servoPin;
    uint8_t angle;
    uint8_t minAngle;
    uint8_t maxAngle;

    int8_t direction;
    uint16_t stepIntervalMs;
    unsigned long lastStepTime;

    bool running;
    bool threatDetected;

public:
    ServoScanner(
        uint8_t pin,
        uint8_t minimumAngle = 0,
        uint8_t maximumAngle = 90,
        uint16_t stepInterval = 17
    );

    void begin();
    void update();
    uint8_t getAngle() const;
    void moveToAngle(uint8_t targetAngle);
    void openBridge();
    void stop();
};

#endif
