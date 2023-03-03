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
#include <cmath>

//#include "VisionSensor.h"

using namespace vex;
int collisionRange = 600;
int stopRange = 300;
int maxSpeed = 20;
int snapshotBuffer = 100;
float incrementMod = 0.5;
float xSpeed = 0;
float ySpeed = 0;

float map(float inputValue, float a1, float a2, float b1, float b2) {
  float output = b1 + (((inputValue - a1) * (b2 - b1)) / (a2 - a1));
  return output;
  // maps one value in a range to its corresponding value in another range
}

float fishX() {
  // VisionSensor.takeSnapshot(VisionSensor__FISH);
  float x =
      map(VisionSensor.largestObject.centerX, 90, 240, -maxSpeed, maxSpeed);
  return x;
  // outputs the fishes x value, ranges from negative max speed to max speed
}

float fishY() {
  // VisionSensor.takeSnapshot(VisionSensor__FISH);
  float y =
      map(VisionSensor.largestObject.centerY, 185, 40, -maxSpeed, maxSpeed);
  return y;
  // outputs the fishes y value, ranges from negative max speed to max speed
}

float depthCollision(float ySpeed) {
  if ((RangeFront.distance(mm) < stopRange && ySpeed > 0) /*||
      (RangeBack.distance(mm) < stopRange && ySpeed < 0)*/) {
    return 0;
  }
  // set speed to 0 if within stop range of wall

  else if (ySpeed > 0 && RangeFront.distance(mm) <= collisionRange) {

    return ySpeed * (map(RangeFront.distance(mm), 0, collisionRange, 0, 1));
  }
  // if front gets within the collision distance, the speed gets slower as it
  // approaches.

  else if (ySpeed < 0 && RangeBack.distance(mm) <= collisionRange) {

    return ySpeed * (map(RangeBack.distance(mm), 0, collisionRange, 0, 1));
  }
  // if back gets within the collision distance, the speed gets slower as it
  // approaches

  else {
    return ySpeed;
  }
}

float widthCollision(float xSpeed) {
  if ((RangeRight.distance(mm) < stopRange && xSpeed > 0) ||
      ((RangeLeft.distance(mm) < stopRange) && xSpeed < 0)) {
    return 0;
  }
  // set speed to 0 if within stop range of wall

  else if (xSpeed > 0 && RangeRight.distance(mm) <= collisionRange) {

    return xSpeed * (map(RangeRight.distance(mm), 0, collisionRange, 0, 1));
  }
  // if right gets within the collision distance, the speed gets slower as it
  // approaches

  else if (xSpeed < 0 && RangeLeft.distance(mm) <= collisionRange) {

    return xSpeed * (map(RangeLeft.distance(mm), 0, collisionRange, 0, 1));
  }
  // if left gets within the collision distance, the speed gets slower as it
  // approaches

  else {
    return xSpeed;
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  MotorsHorizontal.spin(forward);
  MotorsVertical.spin(forward);

  
  while (true) {
    // int millisTimer = (Brain.Timer.value() * 1000);
    // if (millisTimer % snapshotBuffer == 0) {
    VisionSensor.takeSnapshot(VisionSensor__FISH);
    //}

    float xDiff = fishX() - xSpeed;
    float yDiff = fishY() - ySpeed;
    // difference between where the target speed is and the current speed

    if (fabs((1 / xDiff) * incrementMod) > fabs(fishX())) {
      xSpeed = fishX();
      // if the amount it would incrament is larger than the target speed,
      // current speed is set to target speed
    } else {
      xSpeed += ((1 / xDiff) * incrementMod);
      // as the current speed gets closer to the target speed, the rate of
      // acceleration increases
    }

    if (fabs((1 / yDiff) * incrementMod) > fabs(fishY())) {
      ySpeed = fishY();
      // if the amount it would incrament is larger than the target speed,
      // current speed is set to target speed
    } else {
      ySpeed += ((1 / yDiff) * incrementMod);
      // as the current speed gets closer to the target speed, the rate of
      // acceleration increases
    }
     MotorsHorizontal.setVelocity(widthCollision(xSpeed), percent);
     MotorsVertical.setVelocity(depthCollision(ySpeed), percent);

   
   
  }
}