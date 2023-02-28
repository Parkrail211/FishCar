#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor MotorsHorizontalMotorA = motor(PORT13, ratio18_1, false);
motor MotorsHorizontalMotorB = motor(PORT15, ratio18_1, true);
motor_group MotorsHorizontal = motor_group(MotorsHorizontalMotorA, MotorsHorizontalMotorB);
motor MotorsVerticalMotorA = motor(PORT14, ratio18_1, false);
motor MotorsVerticalMotorB = motor(PORT16, ratio18_1, true);
motor_group MotorsVertical = motor_group(MotorsVerticalMotorA, MotorsVerticalMotorB);
sonar RangeFront = sonar(Brain.ThreeWirePort.C);
controller Controller1 = controller(primary);
sonar RangeBack = sonar(Brain.ThreeWirePort.G);
sonar RangeRight = sonar(Brain.ThreeWirePort.E);
/*vex-vision-config:begin*/
signature VisionSensor__FISH = signature (1, 2521, 6089, 4305, -2415, -1143, -1779, 1.4, 0);
vision VisionSensor = vision (PORT3, 79, VisionSensor__FISH);
/*vex-vision-config:end*/
sonar RangeLeft = sonar(Brain.ThreeWirePort.A);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}