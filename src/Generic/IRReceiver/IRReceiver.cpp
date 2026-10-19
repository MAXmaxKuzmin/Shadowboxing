
#include "IRReceiver.h"
#include <IRremote.hpp>

IRReceiver::IRReceiver(uint8_t pin) : receivePin(pin) {}

void IRReceiver::begin() {
    IrReceiver.begin(receivePin, ENABLE_LED_FEEDBACK);
}

uint8_t IRReceiver::update() {
    if (!IrReceiver.decode()) return 100;

    uint8_t command = IrReceiver.decodedIRData.command;
    IrReceiver.resume();
    return command;
}
