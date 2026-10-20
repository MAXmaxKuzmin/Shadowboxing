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
  7, 8, 6, //Left motor
  7, 8, 5, //Right motor
  A5, A4, 9, 10, //Ir analog and Lora
  13, 12, 4, //Ultrasonic and IR receiver
  300 , "NAG" //Threshold and name
);

// Add the D9-specific sensors and actuators to the shared platform.
TagashPlatform tagash(
    basePlatform,
    9 // Servo pin
);

// Initializes serial diagnostics and all platform hardware.
void setup() {
    Serial.begin(9600);
    tagash.begin();
}

void loop() {
    // Wait until the hamal selects the north or south mission.
    while(missionNotStarted) {
      String command = tagash.getGenericPlatform().listen();
      String type = command.substring(0, command.indexOf('|'));
      if (type == "NORTH") {
        missionNotStarted = false;
    }

    // Wait until the hamal authorizes the platform to start moving.
    while(MoveNotStarted) {
      String command = tagash.getGenericPlatform().listen();
      String type = command.substring(0, command.indexOf('|'));
      if (type == "GO") {
        MoveNotStarted = false;
      }
    }

    if (!finished) {
        tagash.getGenericPlatform().driveUntilFoundIR(1);
        tagash.openBridge();
        finished = true;
        tagash.getGenericPlatform().sendMessage("HML", "FIN", 0, 0);
    }
}
}
