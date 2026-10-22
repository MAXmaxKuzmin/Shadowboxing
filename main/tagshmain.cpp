#include "Generic/GenericPlatform/GenericPlatform.h"
#include <Arduino.h>
#include "Tagash/Tagash/Tagash.h"

// Keeps the program waiting for the mission selection command.
bool missionNotStarted = true;

// Keeps the program waiting for the command to begin movement.
bool MoveNotStarted = true;

bool finished = false;

// Identifies the two possible mission routes.
enum Mission {
  NORTH,
  SOUTH
} mission;

// Left motor: IN1=7, IN2=8, EN=5
// Right motor: IN1=7, IN2=8, EN=6
// IR sensors: left=A4, right=A5, lora communication: TX=2, RX=3
// Sonic sensor: TRIG=13, ECHO=12, IR receiver: 4
// The threshold for line detection is set to 200 (for analog sensors).

GenericPlatform basePlatform(
  4, 6, 9, //Left motor
  4, 6, 9, //Right motor
  A0, A1, 2, 3, //Ir analog and Lora
  100, 100, 11, //Ultrasonic and IR receiver
  300 , "TAG" //Threshold and name
);

// Add the D9-specific sensors and actuators to the shared platform.
TagashPlatform tagash(
    basePlatform,
    13,
    12,
    5
);

// Initializes serial diagnostics and all platform hardware.
void setup() {
    Serial.begin(9600);
    tagash.begin();
}

void loop() {
    tagash.getGenericPlatform().driveForXseconds(5);
    tagash.openBridge();
    tagash.getGenericPlatform().endMission();
    delay(1000);
}

