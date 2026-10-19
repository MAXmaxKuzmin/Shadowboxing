
#ifndef IR_RECEIVER_H
#define IR_RECEIVER_H

#include <Arduino.h>

class IRReceiver {
private:
    uint8_t receivePin;

public:
    explicit IRReceiver(uint8_t pin);
    void begin();
    uint8_t update();
};

#endif
