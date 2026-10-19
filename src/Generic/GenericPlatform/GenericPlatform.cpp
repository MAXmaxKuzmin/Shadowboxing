#include "GenericPlatform.h"

#define BASE_PWM 100
#define KP 50
#define V_BASE_CMPS 20.0f


using namespace std;

static uint16_t getDistance(uint8_t ir) {
  switch (ir) {
    case 16: return 497;
    case 15: return 0;
    case 14: return 367;
    case 13: return 348;
    case 12: return 258;
    case 11: return 98;
    case 4:  return 219;
    case 3:  return 295;
    case 2:  return 102;
    case 1:  return 0;
    case 0:  return 1000;
    default: return 0;
  }
}
GenericPlatform::GenericPlatform(
  uint8_t li1, uint8_t li2, uint8_t le,
  uint8_t ri1, uint8_t ri2, uint8_t re,
  uint8_t lir, uint8_t rir,
  uint8_t tx, uint8_t rx,
  uint8_t trig, uint8_t echo,
  uint8_t ir, uint16_t threshold, const String& name
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
    irReceiver(ir),
    distanceTravelled(0.0f) {}

void GenericPlatform::begin() {
  driveSystem.begin();
  lineFollower.begin();
  comunication.begin();
  sonic.begin();
  irReceiver.begin();
}

float GenericPlatform::updateDrive() {
  unsigned long currentTime = millis();
  static unsigned long lastLoopTime = 0;

  if (lastLoopTime == 0) {
    lastLoopTime = currentTime;
    return distanceTravelled;
  }
  float dt = (currentTime - lastLoopTime) / 1000.0f;
  int correction = KP * lineFollower.update();
  Serial.print(F("Correction: "));
  Serial.println(correction);

  if (correction / KP == 2) {
    Serial.println(F("Line lost! Stopping."));
    driveSystem.stop();
    return distanceTravelled;
  }

  int leftPWM = constrain(BASE_PWM - correction, 0, 255);
  int rightPWM = constrain(BASE_PWM + correction, 0, 255);

  float vL = V_BASE_CMPS * ((float)leftPWM / BASE_PWM);
  float vR = V_BASE_CMPS * ((float)rightPWM / BASE_PWM);

  // Serial.print(F("Left PWM: "));
  // Serial.print(leftPWM);
  // Serial.print(F(", Right PWM: "));
  // Serial.print(rightPWM);
  // Serial.print(F(", vL: "));
  // Serial.print(vL);
  // Serial.print(F(", vR: "));
  // Serial.println(vR);

  distanceTravelled += (vL + vR) * 0.5f * dt;
  // Serial.print(F("Distance travelled: "));
  // Serial.println(distanceTravelled);

  // Serial.print(F("Left PWM: "));
  // Serial.print(leftPWM);
  // Serial.print(F(", Right PWM: "));
  // Serial.println(rightPWM);


  driveSystem.drive(leftPWM, rightPWM);
  return distanceTravelled;
}

String GenericPlatform::listen() {
  return comunication.listen();
}

void GenericPlatform::sendMessage(
  const String& to, const String& type,
  int x, int angle
) {
  comunication.sendMessage(to, type, x, angle);
}

float GenericPlatform::checkSonicDistance() {
  return sonic.readDistanceCm();
}

uint8_t GenericPlatform::updateIRReceiver() {
  int ir = irReceiver.update();
  distanceTravelled = getDistance(ir);
  return ir;
}

void GenericPlatform::stopDrive() {
  driveSystem.stop();
}

float GenericPlatform::totalDistance() {
  return distanceTravelled;
}
