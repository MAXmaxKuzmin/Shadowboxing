
#include "IRReceiver.h"
#include <IRremote.hpp>

IRReceiver::IRReceiver(uint8_t pin)
    : receivePin(pin) {
}

void IRReceiver::begin() {
    IrReceiver.begin(receivePin, ENABLE_LED_FEEDBACK);
}

uint8_t IRReceiver::update() {
    if (IrReceiver.decode()) {
        Serial.println(F("\n[Signal Received]"));
        Serial.println(IrReceiver.decodedIRData.command);
        IrReceiver.resume();
        return IrReceiver.decodedIRData.command;
    }
    return 100;
}
