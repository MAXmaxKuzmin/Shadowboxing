#include "Generic/GenericPlatform/GenericPlatform.h"
#include <Arduino.h>
#include "D9/D9/D9.h"

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

GenericPlatform basePlatform(
  7, 8, 6, //Left motor
  7, 8, 5, //Right motor
  A5, A4, 9, 10, //Ir analog and Lora
  13, 12, 4, //Ultrasonic and IR receiver
  300 , "NAG" //Threshold and name
);

// Add the D9-specific sensors and actuators to the shared platform.
D9Platform d9(
    basePlatform,
    A3, // LDR pin
    300, // Laser threshold
    9 // Servo pin
);

// Initializes serial diagnostics and all platform hardware.
void setup() {
    Serial.begin(9600);
    d9.begin();
}

void loop() {

    // Wait until the hamal selects the north or south mission.
    while(missionNotStarted) {
      String command = d9.getGenericPlatform().listen();
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
      String command = d9.getGenericPlatform().listen();
      String type = command.substring(0, command.indexOf('|'));
      if (type == "FIN") {
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

void northLoop() {
  d9.getGenericPlatform().driveUntilFoundIR(2);
  d9.findEnemy();

  d9.getGenericPlatform().updateDrive();
  d9.getGenericPlatform().listen();
  d9.getGenericPlatform().sendLocationIfDue();

  // Notify the controller that the northbound mission is complete.
  d9.getGenericPlatform().sendMessage("HML", "FIN", 0, 0);

// Remain available for incoming messages while periodically reporting location.
while (true) {
    d9.getGenericPlatform().listen();
    d9.getGenericPlatform().sendLocationIfDue();
}
}

void southLoop() {
    d9.getGenericPlatform().driveUntilFoundIR(11);
    d9.findEnemy();
    d9.getGenericPlatform().driveUntilFoundIR(13);
    d9.findEnemy();
    //d9.Tow();
    d9.getGenericPlatform().driveUntilFoundIR(16);
    //d9.mignan();

    // Notify the controller that the southbound mission is complete.
    d9.getGenericPlatform().sendMessage("HML", "FIN", 0, 0);

    // Remain available for incoming messages while periodically reporting location.
    while (true) {
        d9.getGenericPlatform().listen();
        d9.getGenericPlatform().sendLocationIfDue();
    }
}
