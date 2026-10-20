
#include "LineFollower.h"

LineFollower::LineFollower(
  IRSensor& left,
  IRSensor& right
)
  : leftSensor(left),
    rightSensor(right) {}

int8_t LineFollower::update() {
  bool left = leftSensor.detectsLine();
  Serial.print("Left Sensor: ");
  Serial.print(left);
  bool right = rightSensor.detectsLine();
  Serial.print(", Right Sensor: ");
  Serial.println(right);

  if (left && right) {
    return 0;
  } else if (left && !right) {
    return -1;
  } else if (!left && right) {
    return 1;
  } else {
    return 2;
  }
}

void LineFollower::begin() {
    leftSensor.begin();
    rightSensor.begin();
}

