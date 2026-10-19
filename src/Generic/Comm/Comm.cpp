
#include "Comm.h"

Comm::Comm(
  uint8_t txdPin,
  uint8_t rxdPin,
  String name

)
  : loraSerial(txdPin, rxdPin),
    sender(name)
{}

void Comm::begin() {
  loraSerial.begin(9600);
}

void Comm::sendMessage(String to, String type, int x, int angle) {
  static int counter = 0;
  String msg = (String)sender + "|" +
               (String)to + "|" +
               (String)type + "|" +
               String(x) + "|" +
               String(angle) + "|" + String(counter++);
  loraSerial.println(msg);
}

String Comm::listen() {
  while (loraSerial.available()) {
    String message = loraSerial.readStringUntil('\n');
    String from = message.substring(0, message.indexOf('|'));
    String to = message.substring(message.indexOf('|') + 1, message.indexOf('|', message.indexOf('|') + 1));

    if (to != this->sender && to != "ALL") {
      return "";
    }

    String type = message.substring(message.indexOf('|', message.indexOf('|') + 1) + 1, message.indexOf('|', message.indexOf('|', message.indexOf('|') + 1) + 1));
    // Serial.print("Received message: ");
    // Serial.println(type);
    return type;
  }
  return "";
}
