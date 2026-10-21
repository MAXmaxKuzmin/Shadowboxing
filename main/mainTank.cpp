#include "Generic/GenericPlatform/GenericPlatform.h"
#include <Arduino.h>
#include "Tank/Tank/Tank.h"

#define LAST_NORTH_IR 2
#define LAST_SOUTH_IR 16

// Keeps the program waiting for the mission selection command.
bool missionNotStarted = true;

// Keeps the program waiting for the command to begin movement.
bool MoveNotStarted = true;
bool firstMove = false;

bool foundAllThreats = false;

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
TankPlatform tank(
    basePlatform,
    9, // mic pin
    300, // sound threshold
    A3 // Servo pin
);

// Initializes serial diagnostics and all platform hardware.
void setup() {
    Serial.begin(9600);
    tank.begin();
}

void loop() {
    // Wait until the hamal selects the north or south mission.
    while(missionNotStarted) {
      String command = tank.getGenericPlatform().listen();
      if (tank.getGenericPlatform().needToStop()) {
        tank.getGenericPlatform().endMission();
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

    while(!foundAllThreats) {
      String command = tank.getGenericPlatform().listen();
      if (tank.getGenericPlatform().needToStop()) {
        tank.getGenericPlatform().endMission();
        break;
      }
      if (firstMove) {
        tank.getGenericPlatform().sendLocationIfDue();
      }
      if (command == "") {
          delay(100);
          continue;
      }
      firstMove = true;
      String type = command.substring(0, command.indexOf('|'));
      if (type == "THREAT") {
        MoveNotStarted = false;
        String x = command.substring(command.indexOf('|') + 1, command.lastIndexOf('|'));
        String angle = command.substring(command.lastIndexOf('|') + 1);
        tank.getGenericPlatform().driveUntilFoundIR(x.toInt());
        tank.shoot(angle.toInt());
      } else if (type == "GO") {
        foundAllThreats = true;
      }
    }
    tank.getGenericPlatform().driveUntilTheEnd();
    tank.getGenericPlatform().endMission();

}
