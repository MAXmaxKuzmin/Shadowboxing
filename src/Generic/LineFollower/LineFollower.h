
#ifndef LINE_FOLLOWER_H
#define LINE_FOLLOWER_H

#include "../IRSensor/IRSensor.h"
#include "../TankDrive/TankDrive.h"

class LineFollower {
private:
  IRSensor& leftSensor;
  IRSensor& rightSensor;

public:
  LineFollower(
    IRSensor& left,
    IRSensor& right
  );

  byte update();

  void begin();
};

#endif
