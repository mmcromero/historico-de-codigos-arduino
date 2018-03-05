// MultiStepper
// -*- mode: C++ -*-
//
// Control both Stepper motors at the same time with different speeds
// and accelerations. 
// Requires the AFMotor library (https://github.com/adafruit/Adafruit-Motor-Shield-library)
// And AccelStepper with AFMotor support (https://github.com/adafruit/AccelStepper)
// Public domain!

#include <AccelStepper.h>
#include <AFMotor.h>

// two stepper motors one on each port
AF_Stepper motor1(2048, 1);
AF_Stepper motor2(2048, 2);

// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
// wrappers for the first motor!
void forwardstep1() {  
  motor1.onestep(FORWARD, SINGLE  );
}
void backwardstep1() {  
  motor1.onestep(BACKWARD, SINGLE  );
}
// wrappers for the second motor!
void forwardstep2() {  
  motor2.onestep(FORWARD, SINGLE  );
}
void backwardstep2() {  
  motor2.onestep(BACKWARD, SINGLE  );
}

// Motor shield has two motor ports, now we'll wrap them in an AccelStepper object
AccelStepper stepper1(backwardstep1, forwardstep1);
AccelStepper stepper2(backwardstep2, forwardstep2);



String cmd = "";



void setup()
{  
  Serial.begin(9600);
  
    stepper1.setMaxSpeed(100);
    stepper1.setAcceleration(100);
    stepper1.moveTo(1500);
    
    stepper2.setMaxSpeed(100);
    stepper2.setAcceleration(100);
    stepper2.moveTo(1500);
    
}

void loop()
{
  
  
  
  /////// RECEBE SERIAL //-----------------------------------------------------------------------------------------------------------

  if(Serial.available() > 0) // serial pc
  {
    while(Serial.available() > 0)
    {
      cmd += char(Serial.read());
      delay(10);
    }
    Serial.println(cmd); 
  }
  

  
  if (cmd.length() >0) { 

    
    if(cmd == "1"){  inverte1(); }
    if(cmd == "2"){  inverte2(); }
    
    cmd = "";
  }
  
  //-----------------------------------------------------------------------------------------------------------------------------
  
    // Change direction at the limits
    stepper1.run();	
    stepper2.run();
    Serial.println(stepper1.currentPosition());
}



void inverte1()
{   
  stepper1.moveTo(0);
  stepper2.moveTo(0);
} 

void inverte2()
{   
  stepper1.moveTo(stepper1.currentPosition() -750);
  stepper2.moveTo(stepper2.currentPosition() +750);
} 
