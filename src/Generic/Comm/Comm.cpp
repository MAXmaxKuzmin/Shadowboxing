
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

void Comm::sendMessage(String to, String type, int x, int angle, int counter) {
  String msg = (String)sender + "|" +
               (String)to + "|" +
               (String)type + "|" +
               String(x) + "|" +
               String(angle) + "|" + String(counter);
  loraSerial.println(msg);
}

String Comm::listen() {
  while (loraSerial.available()) {
    String message = loraSerial.readStringUntil('\n');
    String from = message.substring(0, message.indexOf('|'));
    String to = message.substring(message.indexOf('|') + 1, message.indexOf('|', message.indexOf('|') + 1));
    String type = message.substring(message.indexOf('|', message.indexOf('|') + 1) + 1, message.indexOf('|', message.indexOf('|', message.indexOf('|') + 1) + 1));
    String xStr = message.substring(message.indexOf('|', message.indexOf('|', message.indexOf('|') + 1) + 1) + 1, message.indexOf('|', message.indexOf('|', message.indexOf('|', message.indexOf('|') + 1) + 1) + 1));
    String angleStr = message.substring(message.indexOf('|', message.indexOf('|', message.indexOf('|', message.indexOf('|') + 1) + 1) + 1) + 1, message.indexOf('|', message.indexOf('|', message.indexOf('|', message.indexOf('|', message.indexOf('|') + 1) + 1) + 1) + 1) + 1);
    String counterStr = message.substring(message.lastIndexOf('|') + 1);

    if (to != this->sender && to != "ALL") {
      return "";
    }

    // Convert the string values to integers
    int x = xStr.toInt();
    int angle = angleStr.toInt();
    int counter = counterStr.toInt();

    sendMessage(from, "ACK", x, angle, counter);
    // Serial.print("Received message: ");
    // Serial.println(type);

    return type;
  }
  return "";
}
