/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Sun Nov 6 2022                                          */
/*    Description:  Left AWP                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    11, 13, 14, 15, 16, 20        
// Shooter              motor         3               
// Intake               motor         12  
// Shooter_pneum        digital_out   A
// String               digital_out   B             
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h" 

using namespace vex;

// A global instance of competition
competition Competition;
long pid_turn_by(double angle);
long pid_drive(double distance, int32_t time=60000, double space=0, double drivekp = 12);

bool vision_in_prog = false; 
#define PRINT_LEVEL_MUST 0
#define PRINT_LEVEL_NORMAL 1
#define PRINT_LEVEL_DEBUG 2

#define DEBUG_LEVEL PRINT_LEVEL_DEBUG

#define DEBUG_PRINT(dl, fmt, args...) {if (dl <= DEBUG_LEVEL) printf(fmt, ## args);}

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  //Rotation.setPosition(0, degrees); // Rotation.resetPosition();
  Drivetrain.setDriveVelocity(100, percent);
  cata.setVelocity(100, percent);
  Drivetrain.setStopping(hold);
  Inertia.calibrate();
  
}

// AUTON FUNCTIONS

void tdrivefor(double rotation, double power, int32_t time) {
  Drivetrain.setTimeout(time, msec);
  Drivetrain.setDriveVelocity(power, percent);
  Drivetrain.driveFor(forward, rotation, inches);
}
void tdriverev(double rotation, double power, int32_t time) {
  Drivetrain.setTimeout(time, msec);
  Drivetrain.setDriveVelocity(power, percent);
  Drivetrain.driveFor(reverse, rotation, inches);
}
bool cat = false;
// **** CATAPULT TESTING ****
void cata_loop(void) {
  if (Debounce.value() < 0.1) {
      return;
    }
  Debounce.reset();
  if (cat == false) {
    cata.spin(forward, 20, volt);
    cat = true;
  }
  else if (cat == true){
    cata.stop();
    cat = false;
  }
  }


void cata_load(void) {
  if (Debounce.value() < 0.1) {
    return;
  }
  Debounce.reset();
  cata.setVelocity(100, percent);
  cata.spinFor(110, degrees, true);
}

void cata_shoot(void) {
  if (Debounce.value() < 0.1) {
    return;
  }
  Debounce.reset();
  cata.setVelocity(100, percent);
  cata.spinFor(250, degrees, true);  
}

void cata_adjust(void) {

  cata.setVelocity(100, percent);
  cata.spinFor(10, degrees, true);
}

void cata_down30(void) { // DON'T USE THIS
  double rot_deg = Rotation.position(degrees);
  cata.setVelocity(100, percent);
  cata.spinFor(10, degrees, true);
  printf("rot_deg %f", rot_deg);

}

void cata_stop(void) {
  cat = false;
}

void cata_rot(double deg) { // DON'T USE THIS

  while (true) {
    if (deg > Rotation.position(degrees)) {
      cata.spin(forward, 5, volt); // direction may be wrong
    }
    else {
      cata.stop();
      break;
    }
  }
}


void cata_button() { // DON'T USE THIS
  cata_rot(175); // change degrees depending on how far you need it to go
}

// Intake Functions
bool int_spin = false;
void intake_spin(void) {
  if (Debounce.value() < 0.1) {
    return;
  }
  Debounce.reset();
  if (int_spin == false) {
    intake.spin(forward, 100, percent);
    int_spin = true;
    printf("hi \n");
  }
  else{
    intake.stop();
    int_spin = false;
    printf("hi2 \n");
  }
}

bool int_spin2 = false;
void intake_spin2(void) {
  if (Debounce.value() < 0.1) {
    return;
  }
  Debounce.reset();
  if (int_spin2 == false) {
    intake.spin(reverse, 100, percent);
    int_spin2 = true;
    printf("hello \n");
  }
  else{
    intake.stop();
    int_spin2 = false;
    printf("hello2 \n");
  }
}

void intake_stop(void) {
  intake.stop();
}

// wings
bool w1 = false;
void wing1_move(void) {
  if (Debounce.value() < 0.1) {
      return;
    }
  Debounce.reset();
  if (w1 == false) {
    wing1.set(true);
    w1 = true;
  }
  else {
    wing1.set(false);
    w1 = false;
  }
}

bool w2 = false;
void wing2_move(void) {
  if (Debounce.value() < 0.1) {
      return;
    }
  Debounce.reset();
  if (w2 == false) {
    wing2.set(true);
    w2 = true;
  }
  else {
    wing2.set(false);
    w2 = false;
  }
}

void double_wing(void) {
  if (Debounce.value() < 0.1) {
      return;
    }
  Debounce.reset();
  if (w1 == false && w2 == false) {
    wing1.set(true);
    w1 = true;
    wing2.set(true);
    w2 = true;
  }

  else if(w1 == true && w2 == true) {
    wing1.set(false);
    w1 = false;
    wing2.set(false);
    w2 = false;
  }
}

// blocker
// bool block = false;
// void block_move(void) {
//   if (Debounce.value() < 0.1) {
//       return;
//     }
//   Debounce.reset();
//   if (block == false) {
//     blocker.set(true);
//     block = true;
//   }
//   else {
//     blocker.set(false);
//     block = false;
//   }
// }

// climber

bool c = false;
void climb_move(void) {
  if (Debounce.value() < 0.1) {
      return;
    }
  Debounce.reset();
  if (c == false) {
    climb.set(true);
    c = true;
  }
  else {
    climb.set(false);
    c = false;
  }
}

// arm

// void move_arm_down(void) {
//   arm.setVelocity(100, percent);
//   arm.setTimeout(1000, msec);
//   arm.spinFor(forward, 135, degrees);
// }

// void move_arm_up(void) {
//   arm.setVelocity(100, percent);
//   arm.setTimeout(3000, msec);
//   arm.spinFor(reverse, 135, degrees);
// }

//drives robot backward
// rotation: how many turns of the wheel to travel backward
// power: velocity of wheels in percentage
void driveBackward(double rotation, double power, int32_t time) {
  Drivetrain.setTimeout(time, msec);
  Drivetrain.setDriveVelocity(power, percent);
  Drivetrain.driveFor(reverse, rotation, inches);
}

//drives robot forward
// rotation: how many turns of the wheel to travel backward
// power: velocity of wheels in percentage
void driveForward(double rotation, double power, int32_t time) {
  Drivetrain.setTimeout(time, msec);
  Drivetrain.setDriveVelocity(power, percent);
  Drivetrain.driveFor(forward, rotation, inches);
}

void autonomous(void) {
  intake.setVelocity(50, percent);
  Drivetrain.setStopping(hold);
  wing2_move();
  //wait(1, sec);
  pid_drive(-10, 1000, 0, 20);
  //pid_turn_by(45);
  wait(1, sec);
  wing2_move();
  wait(0.2, sec);
  pid_turn_by(55);
  pid_drive(-15, 1500, 0, 30);
  pid_drive(3);
  pid_turn_by(-45);
  pid_drive(10);
  pid_turn_by(70);
  pid_drive(-25);
  pid_turn_by(-40);
  double_wing();
  pid_drive(-17, 2500, 0, 30);
  pid_drive(5);
  double_wing();
  
  
  

  }


// USER CONTROL
  

double drive_kp = 20;
double drive_ki = 0.0015;
double drive_kd = 0.09;
double drive_tolerance = 0.1;    // we want to stop when we reach the desired angle +/- 1 degree

long pid_drive(double distance, int32_t time, double space, double drivekp) {
  double delay = 20;   // Inertia can output reading at a rate of 50 hz (20 msec)
  long loop_count = 0;
  double error = 5000;
  double total_error = 0;
  double derivative = 0.1;
  double prev_error = 0;
  double voltage = 0;
  double min_volt = 2.5;   // we don't want to apply less than min_volt, or else drivetrain won't move
  double max_volt = 11.5;  // we don't want to apply more than max volt, or else we may damage motor
  bool direction = true;
  double rotation = distance / (4 * M_PI);
  double current_rotation = (RightDriveSmart.position(turns) + LeftDriveSmart.position(turns)) / 2;
  rotation += current_rotation;
  double start_time = PidDriveTimer.time(msec);
  double current_space = 144;
  // if (dist_sensor.isObjectDetected()) {
  //   current_space = dist_sensor.objectDistance(inches);
  // }

  //DEBUG_PRINT(PRINT_LEVEL_NORMAL, "Drive by distance %.2f, current_space %.2f, space %.2f\n", distance, current_space, space);
  // keep turning until we reach desired angle +/- tolerance
  while ((error > drive_tolerance) && (PidDriveTimer.time(msec) < (start_time + time)) && (current_space >= space )) {
    current_rotation = (RightDriveSmart.position(turns) + LeftDriveSmart.position(turns)) / 2;
    error = rotation - current_rotation;
    if (error < 0) {
      error = error * -1;
      direction = false;
    } else {
      direction = true;
    }
    total_error += error;   // used for integration term
    derivative = error - prev_error;
    voltage = drivekp * error + drive_ki * total_error - drive_kd * derivative;
    if (voltage < min_volt) {
        voltage = min_volt;
      } else if (voltage > max_volt) {
      voltage = max_volt;
    }
    if ((loop_count < 20) && (voltage > min_volt)){
      voltage = min_volt + ((voltage - min_volt) / 20) * loop_count;
    }
    //DEBUG_PRINT(PRINT_LEVEL_DEBUG, "error %.2f, voltage %.2f, direction %d, angle %.2f\n", error, voltage, direction, Inertia.rotation());
    if (direction) {
      RightDriveSmart.spin(forward, voltage, volt);
      LeftDriveSmart.spin(forward, voltage, volt);
    } else {
      RightDriveSmart.spin(reverse, voltage, volt);
      LeftDriveSmart.spin(reverse, voltage, volt);
    }
    prev_error = error;
    // if (dist_sensor.isObjectDetected()) {
    //   current_space = dist_sensor.objectDistance(inches);
    // }
    wait(delay, msec);
    ++loop_count;
  }
  RightDriveSmart.stop();
  LeftDriveSmart.stop();
  //DEBUG_PRINT(PRINT_LEVEL_DEBUG, "drive by distance %.2f, loop count %ld\n", distance, loop_count);
  return loop_count;
}

double turn_kp = 0.1; //1.5
double turn_ki = 0.00000001; //0.0009
double turn_kd = 0;
double turn_tolerance = 10.5;    // we want to stop when we reach the desired angle +/- 1 degree

long pid_turn(double angle) {
  double delay = 20;   // Inertia can output reading at a rate of 50 hz (20 msec)
  long loop_count = 0;
  double error = 5000;
  double total_error = 0;
  double derivative = 0;
  double prev_error = 0;
  double voltage = 0;
  double min_volt = 2.5;   // we don't want to apply less than min_volt, or else drivetrain won't move
//  double max_volt = 11.5;  // we don't want to apply more than max volt, or else we may damage motor
  double max_volt = 6.5;  // we don't want to apply more than max volt, or else we may damage motor
  bool direction = true;

  //DEBUG_PRINT(PRINT_LEVEL_NORMAL, "Turn to angle %.2f, current angle %.2f\n", angle, Inertia.rotation());
  // keep turning until we reach desired angle +/- tolerance
  while (error > turn_tolerance) {
    error = angle - Inertia.rotation();
    if (error < 0) {
      error = error * -1;
      direction = false;
    } else {
      direction = true;
    }
    total_error += error;   // used for integration term
    derivative = error - prev_error;
    voltage = turn_kp * error + turn_ki * total_error - turn_kd * derivative;
    if (voltage < min_volt) {
        voltage = min_volt;
      } else if (voltage > max_volt) {
      voltage = max_volt;
    }
    //DEBUG_PRINT(PRINT_LEVEL_DEBUG, "error %.2f, voltage %.2f, direction %d, rotation %.2f\n", error, voltage, direction, Inertia.rotation());
    if (direction) {
      RightDriveSmart.spin(reverse, voltage, volt);
      LeftDriveSmart.spin(forward, voltage, volt);
    } else {
      RightDriveSmart.spin(forward, voltage, volt);
      LeftDriveSmart.spin(reverse, voltage, volt);
    }
    prev_error = error;
    wait(delay, msec);
    ++loop_count;
  }
  RightDriveSmart.stop();
  LeftDriveSmart.stop();
  //DEBUG_PRINT(PRINT_LEVEL_DEBUG, "Turn to angle %.2f, current angle %.2f, loop count %ld\n", angle, Inertia.rotation(), loop_count);
  return loop_count;
}

long pid_turn_by (double angle) 
{
  return pid_turn(Inertia.rotation() + angle);
}

////////////////////////////////////
// Find kp, ki and kd values that make pid most accurate
////////////////////////////////////
void tune_turn_pid(void)
{
  //turn_kp = 0.09; this was original
  turn_kp = 0.1;
  turn_ki = 0.0009;
  turn_tolerance = 0.2;
  turn_kd = 0.0;
  long loop_count;
  int i;
  Inertia.calibrate();
  wait(2, sec);
  for(i = 0; i < 10; ++i) {
    wait(2, sec);
    loop_count = pid_turn(90 * (i + 1));
    //DEBUG_PRINT(PRINT_LEVEL_NORMAL, "kd %.4f, loop count %ld, final angle %.2f\n", turn_kd, loop_count, Inertia.rotation());
  }

}

////////////////////////////////////DRIVE_PID////////////////////////////////////////


////////////////////////////////////
// Find kp, ki and kd values that make pid most accurate
////////////////////////////////////
// void tune_drive_pid(void)
// {
//   drive_kp = 3;
//   drive_ki = 0.0015;
//   drive_kd = 0.09;
//   drive_tolerance = 0.2;
//   long loop_count;
//   int i;
//   for(i = 0; i < 1; ++i) {
//     wait(2, sec);
//     loop_count = pid_drive(96);
//     //DEBUG_PRINT(PRINT_LEVEL_NORMAL, "kd %.4f, loop count %ld, final angle %.2f\n", drive_kd, loop_count, Inertia.rotation());
//   }
//   for(i = 0; i < 1; ++i) {
//     wait(2, sec);
//     loop_count = pid_drive(-96);
//     //DEBUG_PRINT(PRINT_LEVEL_NORMAL, "kd %.4f, loop count %ld, final angle %.2f\n", drive_kd, loop_count, Inertia.rotation());
//   }
// }
////////////////////////drive_pid/////////////////////////////////////


//
// Main will set up the competition functions and callbacks.
//



void usercontrol(void) {
  // User control code here, inside the loop

  double turnImportance = 1;

  while (1) {

    double turnVal = Controller.Axis3.position(percent);
    double forwardVal = Controller.Axis1.position(percent);

    double turnVolts = turnVal * -0.12;
    double forwardVolts = forwardVal * 0.12* (1 - (abs(turnVolts)/12.0) * turnImportance);
    if (turnVolts > 12) {
      turnVolts = 12;
    }
    if (forwardVolts > 12) {
      forwardVolts = 12;
    }
    // 12 - 12 = 0
    // 12 + 12 = 12(due to cap)

    if (vision_in_prog == false) {
      LeftDriveSmart.spin(forward, forwardVolts - turnVolts, voltageUnits::volt);
      RightDriveSmart.spin(reverse, forwardVolts + turnVolts, voltageUnits::volt);
    
    }
    
  Controller.ButtonR1.pressed(cata_load);
  Controller.ButtonR2.pressed(cata_shoot);
  Controller.ButtonL1.pressed(intake_spin2);
  Controller.ButtonL2.pressed(intake_spin);
  Controller.ButtonB.pressed(cata_loop);
  Controller.ButtonRight.pressed(cata_adjust);
  // Controller.ButtonDown.pressed(move_arm_down);
  // Controller.ButtonUp.pressed(move_arm_up);
  Controller.ButtonA.pressed(wing1_move);

  Controller.ButtonY.pressed(wing2_move);
  Controller.ButtonX.pressed(double_wing);
  Controller.ButtonUp.pressed(climb_move);
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
