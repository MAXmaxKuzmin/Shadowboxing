#include "Generic/GenericPlatform/GenericPlatform.h"
#include <Arduino.h>
#include "Nagmash/Nagmash/Nagmash.h"

// Keeps the program waiting for the mission selection command.
bool missionNotStarted = true;

// Keeps the program waiting for the command to begin movement.
bool MoveNotStarted = true;

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

GenericPlatform platform(
  7, 8, 6, //Left motor IN1, IN2, EN
  7, 8, 5, //Right motor IN1, IN2, EN
  A4, A5, //IR sensors, left, right
  A0, A1, //lora communication: TX, RX
  13, 4, //Ultrasonic TRIG, ECHO
  12, //IR receiver
  300, //Threshold
  "NAG" //name
);

// Add the D9-specific sensors and actuators to the shared platform.
NagmashPlatform nagmash(
    platform,
    2, // MP3 TX pin
    3, // MP3 RX pin
    10 // Servo pin
);

// Initializes serial diagnostics and all platform hardware.
void setup() {
    Serial.begin(9600);
    nagmash.begin();
}

void northLoop() {
  nagmash.getGenericPlatform().driveUntilFoundIR(2);
  nagmash.bomb();
  nagmash.getGenericPlatform().driveUntilFoundIR(4);
  nagmash.getGenericPlatform().endMission();
}

void southLoop() {
    nagmash.mp3Play();
    nagmash.getGenericPlatform().driveUntilFoundIR(11);
    nagmash.bomb();
    nagmash.getGenericPlatform().driveUntilFoundIR(13);
    nagmash.mp3Stop();
    nagmash.getGenericPlatform().endMission();
}



void loop() {

    // Wait until the hamal selects the north or south mission.
    while(missionNotStarted) {
      String command = nagmash.getGenericPlatform().listen();
      if (nagmash.getGenericPlatform().needToStop()) {
        nagmash.getGenericPlatform().endMission();
        break;
      }
      String type = command.substring(0, command.indexOf('|'));
      if (type == "NORTH") {
        mission = NORTH;
        missionNotStarted = false;
      } else if (type == "SOUTH") {
        mission = SOUTH;
        missionNotStarted = false;
      }
    }
    // Wait until the hamal authorizes the platform to start moving.
    while(MoveNotStarted) {
      String command = nagmash.getGenericPlatform().listen();
      if (nagmash.getGenericPlatform().needToStop()) {
        nagmash.getGenericPlatform().endMission();
        break;
      }
      String type = command.substring(0, command.indexOf('|'));
      if (type == "GO") {
        MoveNotStarted = false;
      }
    }

    // Run the route selected during the mission setup phase.
    if (mission == NORTH) {
        northLoop();
    } else if (mission == SOUTH) {
        southLoop();
    }
}

