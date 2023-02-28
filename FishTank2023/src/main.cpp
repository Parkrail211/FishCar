/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\parkrail211                                      */
/*    Created:      Mon Feb 06 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// MotorsHorizontal     motor_group   13, 15
// MotorsVertical       motor_group   14, 16
// RangeFront           sonar         C, D
// Controller1          controller
// RangeBack            sonar         G, H
// RangeRight           sonar         E, F
// VisionSensor         vision        3
// RangeLeft            sonar         A, B
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "math.h"
#include "vex.h"

//#include "VisionSensor.h"

using namespace vex;
int collisionRange = 300;
int stopRange = 200;
int maxSpeed = 25;
float incrementAmount = 0.5;
float xSpeed = 0;
float ySpeed = 0;

float map(float inputValue, float a1, float a2, float b1, float b2) {
  float output = b1 + (((inputValue - a1) * (b2 - b1)) / (a2 - a1));
  return output;
}

float fishX() {
  VisionSensor.takeSnapshot(VisionSensor__FISH);
  float x =
      map(VisionSensor.largestObject.centerX, 90, 240, -maxSpeed, maxSpeed);
  return x;
}

float fishY() {
  VisionSensor.takeSnapshot(VisionSensor__FISH);
  float y =
      map(VisionSensor.largestObject.centerY, 185, 40, -maxSpeed, maxSpeed);
  return y;
}

float depthCollision(float ySpeed) {
  if ((RangeFront.distance(mm) < stopRange && ySpeed > 0) /*||
      (RangeBack.distance(mm) < stopRange && ySpeed < 0)*/) {
    return 0;
  }
  // set speed to 0 if within 10cm of wall

  else if (ySpeed > 0 && RangeFront.distance(mm) <= collisionRange) {

    return ySpeed * (map(RangeFront.distance(mm), 0, collisionRange, 0, 1));
  }
  // if front gets within the collision distance, the speed gets slower as it
  // approaches.

  /*else if (ySpeed < 0 && RangeBack.distance(mm) <= collisionRange) {

    return ySpeed * (map(RangeBack.distance(mm), 0, collisionRange, 0, 1));
  }*/
  // if back gets within the collision distance, the speed gets slower as it
  // approaches.

  else {
    return ySpeed;
  }
}

float widthCollision(float xSpeed) {
  if ((RangeRight.distance(mm) < 100 && xSpeed > 0) ||
      ((RangeLeft.distance(mm) < 100) && xSpeed < 0)) {
    return 0;
  }
  // set speed to 0 if within 10cm of wall

  else if (xSpeed > 0 && RangeRight.distance(mm) <= collisionRange) {

    return xSpeed * (map(RangeRight.distance(mm), 0, collisionRange, 0, 1));
  }

  else if (xSpeed < 0 && RangeLeft.distance(mm) <= collisionRange) {

    return xSpeed * (map(RangeLeft.distance(mm), 0, collisionRange, 0, 1));
  }

  else {
    return xSpeed;
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  while (true) {
    VisionSensor.takeSnapshot(VisionSensor__FISH);

    if (xSpeed < fishX()) {
      xSpeed = xSpeed + incrementAmount;

    } else if (xSpeed > fishX()) {
      xSpeed = xSpeed - incrementAmount;
    }

    if (ySpeed < fishY()) {
      ySpeed = ySpeed + incrementAmount;

    } else if (ySpeed > fishY()) {
      ySpeed = ySpeed - incrementAmount;
    }

    MotorsHorizontal.setVelocity(xSpeed, percent);
    MotorsVertical.setVelocity(ySpeed, percent);
    MotorsHorizontal.spin(forward);
    MotorsVertical.spin(forward);
  }
}