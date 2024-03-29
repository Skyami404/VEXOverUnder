#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
controller Controller;

// ADJUST THE PORTS, DONT TOUCH ANYTHING ELSE

motor L1 = motor(PORT15, ratio6_1, true); 
motor L2 = motor(PORT14, ratio6_1, true);
motor L3 = motor(PORT1, ratio6_1, true);
motor_group LeftDriveSmart = motor_group(L1, L2, L3);

motor R1 = motor(PORT2, ratio6_1, false); 
motor R2 = motor(PORT10, ratio6_1, false);
motor R3 = motor(PORT3, ratio6_1, false);
motor_group RightDriveSmart = motor_group(R1, R2, R3);

motor cata = motor(PORT5, ratio36_1, true);
motor intake = motor(PORT9, ratio18_1, false);

int wheelTravel = 4 * M_PI;

drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, wheelTravel, 13.5, 18, inches, 1);

inertial Inertia = inertial(PORT6); 
//rotation Rotation = rotation(PORT5, false); 

digital_out wing1 = digital_out(Brain.ThreeWirePort.D);
digital_out wing2 = digital_out(Brain.ThreeWirePort.E);

digital_out climb = digital_out(Brain.ThreeWirePort.C);

timer PidDriveTimer = timer();
timer Debounce = timer();
timer PidTurnTimer = timer();

// VEXcode generated functions




/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}





