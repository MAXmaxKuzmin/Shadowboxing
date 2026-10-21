#include "Comm.h"

// Initializes the software serial connection and identifies this device as the sender.
Comm::Comm(
  uint8_t txdPin,
  uint8_t rxdPin,
  String name

)
  : loraSerial(txdPin, rxdPin),
    sender(name)
{}

// Starts the LoRa serial link
void Comm::begin() {
  loraSerial.begin(9600);
}

// Serializes a message as sender|recipient|type|x|angle|counter and transmits it.
void Comm::sendMessage(String to, String type, int x, int angle, int counter) {
  String msg = (String)sender + "|" +
               (String)to + "|" +
               (String)type + "|" +
               String(x) + "|" +
               String(angle) + "|" + String(counter);
  loraSerial.println(msg);
  if (type == "ACK") {
    return;
  }
  bool ackReceived = false;
  while (!ackReceived) {
    String ack = Comm::listen();
    if (ack == "STOP") {
      break;
    }
    if (ack.startsWith("ACK")) {
      ackReceived = true;
    }
  }

}

// Reads available messages, acknowledges addressed messages, and returns their type.
String Comm::listen() {
  // Process every complete line currently buffered by the serial connection.
  while (loraSerial.available()) {
    String message = loraSerial.readStringUntil('\n');

    // Extract each protocol field using the pipe separators in the serialized message.
    String from = message.substring(0, message.indexOf('|'));
    String to = message.substring(message.indexOf('|') + 1, message.indexOf('|', message.indexOf('|') + 1));
    String type = message.substring(message.indexOf('|', message.indexOf('|') + 1) + 1, message.indexOf('|', message.indexOf('|', message.indexOf('|') + 1) + 1));

    if (type == "STOP") {
      return "STOP";
    }

    String xStr = message.substring(message.indexOf('|', message.indexOf('|', message.indexOf('|') + 1) + 1) + 1, message.indexOf('|', message.indexOf('|', message.indexOf('|', message.indexOf('|') + 1) + 1) + 1));
    uint16_t x = xStr.toInt();
    String angleStr = message.substring(message.indexOf('|', message.indexOf('|', message.indexOf('|', message.indexOf('|') + 1) + 1) + 1) + 1, message.indexOf('|', message.indexOf('|', message.indexOf('|', message.indexOf('|', message.indexOf('|') + 1) + 1) + 1) + 1) + 1);
    int16_t angle = angleStr.toInt();
    String counterStr = message.substring(message.lastIndexOf('|') + 1);
    uint16_t counter = counterStr.toInt();

    // Ignore messages intended for another device while accepting broadcast messages.
    if (to != this->sender && to != "ALL") {
      return "";
    }

    if (type != "ACK" && type != "STOP") {
      // Confirm receipt using the original message values and return its message type.

      sendMessage(from, "ACK", x, angle, counter);

    }


    return type + "|" + String(x) + "|" + String(angle);
  }

  // Report that no complete message is currently available.
  return "";
}

SoftwareSerial Comm::GetLoraSerial() {
  return loraSerial;
}
