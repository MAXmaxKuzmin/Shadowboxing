
#include "LineFollower.h"

LineFollower::LineFollower(
  IRSensor& left,
  IRSensor& right
)
  : leftSensor(left),
    rightSensor(right) {}

int8_t LineFollower::update() {
  bool left = leftSensor.detectsLine();
  bool right = rightSensor.detectsLine();

  if (left && right) {
    return 0;
  } else if (left && !right) {
    return 1;
  } else if (!left && right) {
    return -1;
  } else {
    return 2;
  }
}

void LineFollower::begin() {
    leftSensor.begin();
    rightSensor.begin();
}

