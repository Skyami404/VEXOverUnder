// DO NOT CHANGE THIS FILE

using namespace vex;
using signature = vision::signature;
extern brain Brain;
extern controller Controller;

// VEXcode devices
extern drivetrain Drivetrain;
extern motor_group LeftDriveSmart;
extern motor_group RightDriveSmart;
extern motor cata1;
extern motor cata2;
extern motor_group cata;
extern motor intake;
extern motor arm;
extern motor climb_m;

extern inertial Inertia;
extern rotation Rotation;

extern digital_out wing1;
extern digital_out wing2;
extern digital_out blocker;

extern timer PidDriveTimer;
extern timer Debounce;


/** 
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
