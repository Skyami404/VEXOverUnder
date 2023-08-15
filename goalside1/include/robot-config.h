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
extern motor arm;

extern inertial Inertia;
extern rotation Rotation;

extern timer PidDriveTimer;
extern timer DebounceTimer;
/** 
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
