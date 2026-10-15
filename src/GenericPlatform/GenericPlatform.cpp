
#include "GenericPlatform.h"

const int BASE_PWM = 160;   // Base PWM command (0 - 255)
const int KP       = 45;
const float V_BASE_CMPS = 20;

GenericPlatform::GenericPlatform(
  uint8_t li1, uint8_t li2, uint8_t le,
  uint8_t ri1, uint8_t ri2, uint8_t re,
  uint8_t lir, uint8_t rir,
  uint8_t tx, uint8_t rx,
  uint8_t trig, uint8_t echo,
  uint8_t ir, uint16_t threshold, String name
)
  : driveSystem(
      Motor(li1, li2, le),
      Motor(ri1, ri2, re)
    ),
    leftSensor(lir, threshold),
    rightSensor(rir, threshold),
    lineFollower(leftSensor, rightSensor),
    comunication(tx, rx, name),
    sonic(trig, echo),
    irReceiver(ir) {}

void GenericPlatform::begin() {
  driveSystem.begin();
  lineFollower.begin();
  comunication.begin();
  sonic.begin();
  irReceiver.begin();
}

int GenericPlatform::updateDrive() {
  static float totalDistance = 0.0;
  static unsigned long lastLoopTime = 0;
  unsigned long currentTime = millis();
  float dt = (currentTime - lastLoopTime) / 1000.0; // Elapsed time in seconds
  lastLoopTime = currentTime;
  int correction = KP * lineFollower.update();
  if (correction / KP == 2) {
    Serial.println(F("Line lost! Stopping."));
    driveSystem.stop();
    return totalDistance;
  }
  
  int leftPWM  = constrain(BASE_PWM - correction, 0, 255);
  int rightPWM = constrain(BASE_PWM + correction, 0, 255);

  // 5. Calculate linear velocity of each track (cm/s) based on PWM ratio
  float v_L = V_BASE_CMPS * ((float)leftPWM / BASE_PWM);
  float v_R = V_BASE_CMPS * ((float)rightPWM / BASE_PWM);

  // 6. Integrate distance: center velocity = average of left and right
  totalDistance += (v_L + v_R) / 2.0 * dt;

  Serial.print("Left PWM: ");
  Serial.print(leftPWM);
  Serial.print(", Right PWM: ");
  Serial.println(rightPWM);
  driveSystem.drive(leftPWM, rightPWM);
  return totalDistance;
}

String GenericPlatform::listen() {
    return comunication.listen();
}

void GenericPlatform::sendMessage(String to, String type, int x, int y, int angle) {
    comunication.sendMessage(to, type, x, y, angle);
}

float GenericPlatform::checkSonicDistance() {
  return sonic.readDistanceCm();
}
uint8_t GenericPlatform::updateIRReceiver() {
  return irReceiver.update();
}

void GenericPlatform::stopDrive() {
  driveSystem.stop();
}







