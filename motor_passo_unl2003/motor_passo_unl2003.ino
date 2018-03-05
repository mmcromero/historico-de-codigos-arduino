#include <AccelStepper.h>
#define HALFSTEP 8

// Motor pin definitions
#define motorPin1  2     // IN1 on the ULN2003 driver 1
#define motorPin2  3     // IN2 on the ULN2003 driver 1
#define motorPin3  4     // IN3 on the ULN2003 driver 1
#define motorPin4  14     // IN4 on the ULN2003 driver 1

#define motorPin5  5     // IN1 on the ULN2803 driver 2
#define motorPin6  6     // IN2 on the ULN2803 driver 2
#define motorPin7  7    // IN3 on the ULN2803 driver 2
#define motorPin8  8    // IN4 on the ULN2803 driver 2

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
AccelStepper stepper2(HALFSTEP, motorPin5, motorPin7, motorPin6, motorPin8);

void setup() {
  
  pinMode(motorPin4, OUTPUT);
  
  
  stepper1.setMaxSpeed(2000.0);
  stepper1.setAcceleration(100.0);
  stepper1.setSpeed(1000);
  stepper1.moveTo(2000);
  
  stepper2.setMaxSpeed(2000.0);
  stepper2.setAcceleration(100.0);
  stepper2.setSpeed(1000);
  stepper2.moveTo(2000);

}//--(end setup )---

void loop() {

  //Change direction when the stepper reaches the target position
  if (stepper1.distanceToGo() == 0) {
    stepper1.moveTo(-stepper1.currentPosition());
  }
  
  if (stepper2.distanceToGo() == 0) {
    stepper2.moveTo(-stepper2.currentPosition());
  }
  
  stepper1.run();
  stepper2.run();
}
