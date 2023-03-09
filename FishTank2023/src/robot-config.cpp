#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor MotorsVerticalMotorA = motor(PORT16, ratio18_1, true);
motor MotorsVerticalMotorB = motor(PORT15, ratio18_1, false);
motor_group MotorsVertical = motor_group(MotorsVerticalMotorA, MotorsVerticalMotorB);
motor MotorsHorizontalMotorA = motor(PORT14, ratio18_1, false);
motor MotorsHorizontalMotorB = motor(PORT13, ratio18_1, true);
motor_group MotorsHorizontal = motor_group(MotorsHorizontalMotorA, MotorsHorizontalMotorB);
sonar RangeFront = sonar(Brain.ThreeWirePort.C);
controller Controller1 = controller(primary);
sonar RangeBack = sonar(Brain.ThreeWirePort.G);
sonar RangeRight = sonar(Brain.ThreeWirePort.E);
/*vex-vision-config:begin*/
signature VisionSensor__FISH = signature (1, 2283, 2721, 2502, -841, -591, -716, 5.6, 0);
vision VisionSensor = vision (PORT6, 116, VisionSensor__FISH);
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