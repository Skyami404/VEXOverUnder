// DO NOT CHANGE THIS FILE

using namespace vex;
using signature = vision::signature;
extern brain Brain;
extern controller Controller;

// VEXcode devices
extern drivetrain Drivetrain;
extern motor_group LeftDriveSmart;
extern motor_group RightDriveSmart;
extern motor cata;
extern motor intake;

extern inertial Inertia;

extern digital_out wing1;
extern digital_out wing2;
extern digital_out climb;

extern timer PidDriveTimer;
extern timer Debounce;
extern timer PidTurnTimer;

/** 
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
