#include <MultiStepper.h>
#include <AccelStepper.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define HALFSTEP 8  //Half-step mode (8 step control signal sequence)

// Motor pin definitions
#define mtrPin1  D1     // IN1 on the ULN2003 driver 1
#define mtrPin2  D2     // IN2 on the ULN2003 driver 1
#define mtrPin3  D5     // IN3 on the ULN2003 driver 1
#define mtrPin4  D6     // IN4 on the ULN2003 driver 1

AccelStepper stepper1(HALFSTEP, mtrPin1, mtrPin3, mtrPin2, mtrPin4);

void setup() {
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(100.0);  //Make the acc quick
  stepper1.setSpeed(300);
  stepper1.moveTo(4096/2);  //Rotate 1 revolution
}

void loop() {

  //Change direction when the stepper reaches the target position
  if (stepper1.distanceToGo() == 0) {
    stepper1.moveTo(-stepper1.currentPosition());  //Reverse motor
  }
  stepper1.run();  //Start
}
