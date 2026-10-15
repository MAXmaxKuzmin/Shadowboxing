
#ifndef TANK_DRIVE_H
#define TANK_DRIVE_H

#include "../Motor/Motor.h"

class TankDrive {
private:
  Motor leftMotor;
  Motor rightMotor;

public:
  TankDrive(const Motor& left, const Motor& right);

  void begin();
  void drive(int leftSpeed, int rightSpeed);
  void stop();
};

#endif
