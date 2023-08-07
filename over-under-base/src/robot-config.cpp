#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller;

// ADJUST THE PORTS, DONT TOUCH ANYTHING ELSE

motor L1 = motor(PORT19, ratio18_1, true); 
motor L2 = motor(PORT9, ratio18_1, true);
motor_group LeftDriveSmart = motor_group(L1, L2);

motor R1 = motor(PORT8, ratio18_1, false); 
motor R2 = motor(PORT18, ratio18_1, false);
motor_group RightDriveSmart = motor_group(R1, R2);

int wheelTravel = 4 * M_PI;

drivetrain Drivetrain = drivetrain(RightDriveSmart, LeftDriveSmart, wheelTravel, 13.5, 18, inches, 1);

motor cata = motor(PORT10, ratio36_1, true);
motor intake = motor(PORT7, ratio18_1, false); 
motor arm = motor(PORT16, false);

inertial Inertia = (PORT2); 
rotation Rotation = (PORT20, false); 

timer PidDriveTimer = timer();

// VEXcode generated functions




/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}





