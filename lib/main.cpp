#include "Generic/GenericPlatform/GenericPlatform.h"


float Distance = 100000;
unsigned long lastMessageTime = 0;
const unsigned long messageInterval = 10000;
const unsigned long locationInterval = 30000UL;
bool missionNotStarted = true;
bool MoveNotStarted = true;
byte SearchIRValue = 2;
bool locationReportingActive = false;
unsigned long lastLocationTime = 0;

enum Mission {
  NORTH,
  SOUTH
} mission;

// Create the hardware platform.
// Left motor: IN1=7, IN2=8, EN=5
// Right motor: IN1=9, IN2=10, EN=6
// IR sensors: left=A0, right=A1, lora communication: TX=12, RX=11
// Sonic sensor: TRIG=3, ECHO=5, IR receiver: 6
// The threshold for line detection is set to 200 (for analog sensors).

#include <Arduino.h>
#include "D9/D9/D9.h"

GenericPlatform basePlatform(
  7, 8, 5,
  7, 8, 6,
  A4, A5, 2, 3,
  13, 12, 4,
  200, "NAG"
);

D9Platform d9(
    basePlatform,
    A3, // LDR pin
    300, // Laser threshold
    9 // Servo pin
);

void sendLocationIfDue() {
    if (!locationReportingActive) return;

    unsigned long currentTime = millis();
    if (currentTime - lastLocationTime >= locationInterval) {
        d9.getGenericPlatform().sendMessage(
            "HML",
            "LOCATION",
            static_cast<int>(d9.getGenericPlatform().totalDistance()),
            0
        );
        lastLocationTime = currentTime;
    }
}

void setup() {
    Serial.begin(9600);
    d9.begin();
}

void loop() {
    sendLocationIfDue();

    while(missionNotStarted) {
      String command = d9.getGenericPlatform().listen();
      if (command == "NORTH") {
        mission = NORTH;
        missionNotStarted = false;
      } else if (command == "SOUTH") {
        mission = SOUTH;
        missionNotStarted = false;
      }
    }
    while(MoveNotStarted) {
      String command = d9.getGenericPlatform().listen();
      if (command == "MOVE") {
        MoveNotStarted = false;
        locationReportingActive = true;
        lastLocationTime = millis();
      }
    }
    if (mission == NORTH) {
        northLoop();
    } else if (mission == SOUTH) {
        southLoop();
    }
}

void northLoop() {
  driveUntilFoundIR(2);
  d9.update();
  d9.getGenericPlatform().updateDrive();
  d9.getGenericPlatform().listen();
  sendLocationIfDue();
}

void southLoop() {
    driveUntilFoundIR(11);
    d9.update();
    driveUntilFoundIR(13);
    d9.update();
    //d9.Tow();
    driveUntilFoundIR(16);
    //d9.mignan();
    d9.getGenericPlatform().sendMessage("HML", "FIN", 0, 0);
    while (true) {
        d9.getGenericPlatform().listen();
        sendLocationIfDue();
    }
}

void driveUntilFoundIR(byte targetIRValue) {
    while (true) {
        d9.getGenericPlatform().updateDrive();
        d9.getGenericPlatform().listen();
        sendLocationIfDue();
        int irValue = d9.getGenericPlatform().updateIRReceiver();
        if (irValue == targetIRValue) {
            d9.getGenericPlatform().stopDrive();
            break;
        }
    }
}
