
#include "TankDrive.h"

TankDrive::TankDrive(const Motor& left, const Motor& right)
  : leftMotor(left), rightMotor(right) {}

void TankDrive::begin() {
  leftMotor.begin();
  rightMotor.begin();
}

void TankDrive::drive(int leftSpeed, int rightSpeed) {
  leftMotor.setSpeed(leftSpeed);
  rightMotor.setSpeed(rightSpeed);
}

void TankDrive::stop() {
  leftMotor.stop();
  rightMotor.stop();
}
