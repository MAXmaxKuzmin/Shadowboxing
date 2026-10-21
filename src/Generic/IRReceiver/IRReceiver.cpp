
#include "IRReceiver.h"
#include <IRremote.hpp>

// Stores the input pin used by the infrared receiver.
IRReceiver::IRReceiver(uint8_t pin) : receivePin(pin) {}

// Initializes the IR receiver and enables feedback on the board LED.
void IRReceiver::begin() {
    IrReceiver.begin(receivePin, ENABLE_LED_FEEDBACK);
}

// Decodes the next available IR command and returns its command value.
uint8_t IRReceiver::update() {
    // Return the project-specific value 100 when no new command is available.
    if (!IrReceiver.decode()) return 100;
    // Read the command from the decoded IR data before accepting another signal.
    uint8_t command = IrReceiver.decodedIRData.command;
    IrReceiver.resume();
    return command;
}
