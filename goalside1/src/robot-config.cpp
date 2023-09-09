#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller;

// ADJUST THE PORTS, DONT TOUCH ANYTHING ELSE

motor L1 = motor(PORT8, ratio18_1, true); 
motor L2 = motor(PORT9, ratio18_1, true);
motor_group LeftDriveSmart = motor_group(L1, L2);

motor R1 = motor(PORT7, ratio18_1, false); 
motor R2 = motor(PORT6, ratio18_1, false);
motor_group RightDriveSmart = motor_group(R1, R2);

motor cata = motor(PORT2, ratio36_1, true);
motor intake = motor(PORT10, ratio18_1, true); 
//motor arm = motor(PORT7, ratio18_1, false);

int wheelTravel = 4 * M_PI;

drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, wheelTravel, 13.5, 18, inches, 1);

inertial Inertia = inertial(PORT5); 
//rotation Rotation = rotation(PORT5, false); 

digital_out wing1 = digital_out(Brain.ThreeWirePort.A); // might need to change piston ports
digital_out wing2 = digital_out(Brain.ThreeWirePort.H);

timer PidDriveTimer = timer();
timer DebounceTimer = timer();

// VEXcode generated functions




/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}





