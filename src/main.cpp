#include "Generic/GenericPlatform/GenericPlatform.h"
#include <Arduino.h>

//bool notStarted = true;
float Distance = 100000;
unsigned long lastMessageTime = 0;
const unsigned long messageInterval = 10000;

// Create the hardware platform.
// Left motor: IN1=7, IN2=8, EN=5
// Right motor: IN1=9, IN2=10, EN=6
// IR sensors: left=A0, right=A1, lora communication: TX=12, RX=11
// Sonic sensor: TRIG=3, ECHO=5, IR receiver: 6
// The threshold for line detection is set to 200 (for analog sensors).
GenericPlatform platform(
  7, 8, 5,
  7, 8, 6,
  A4, A5, 2, 3,
  13, 12, 4,
  200, "NAG"
);

void setup() {
  platform.begin();
  Serial.begin(9600);
}


void loop() {;
  //int totalDistance = 0;
  // if(notStarted) {
  //   while (platform.listen() != "GO") {
  //   // Wait for a valid message
  //   }
  //   notStarted = false; // Set the not started flag to false
  //   lastMessageTime = millis();
  // }
  //platform.listen();
  platform.updateDrive();
  // if (millis() - lastMessageTime >= messageInterval) {
  //   //platform.sendMessage("HML", "DIST", totalDistance, 0, 0);
  //   Serial.print("Total Distance: ");
  //   Serial.println(totalDistance);
  //   lastMessageTime = millis();
  // }
  // Distance = platform.checkSonicDistance();
  // while (Distance < 5) {
  //   Distance = platform.checkSonicDistance();
  //   platform.stopDrive();
  // }
  // if (platform.updateIRReceiver() == 0) {
  //   platform.stopDrive();
  //   delay(5000); // Add a small delay to avoid overwhelming the serial output
  // }

  delay(1000); // Add a small delay to avoid overwhelming the serial output
}
