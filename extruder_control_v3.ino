/*
  Extruder Control - Fletcher Bach, Aaron Nesser 2017

  For use with the Adafruit Motor Shield v2
  ---->  http://www.adafruit.com/products/1438

*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Connect a stepper motor with 10285 steps per revolution (0.035 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(10285, 2);

const int topButtonPin = 7; // buttons to these pins
const int bottomButtonPin = 6;
const int potPin = A2; // potentionmeter to this analog pin on the arduino
float stepSpeed = 0; // e.g. 500 = 1 rpm
const int numberOfSteps = 50;
int potValue = 0;

int topButtonState = 0;
int bottomButtonState = 0;
int lastTopButtonState = 0;
int lastBottomButtonState = 0;

boolean goUp = false;
boolean goDown = false;

int driveDirection = BACKWARD;

void setup() {
  Serial.begin(9600);
  AFMS.begin(1000);  // frequency/inductance for this motor is 1KHz

  // setting up pin modes
  pinMode(topButtonPin, INPUT);
  pinMode(bottomButtonPin, INPUT);

  // set initial motor speed
  myMotor->setSpeed(0);
  delay(100);

}

void loop() {
  // get potentiometer value
  potValue = analogRead(potPin);
  Serial.print("POTENTIOMETER: ");
  Serial.print(potValue);
  //delay(1);

  if (potValue <= 23 || potValue > 1023) {
    stepSpeed = 0;
  }
  else if (potValue > 23 && potValue <= 123) {
    stepSpeed = 0.25;
  }
  else if (potValue > 123 && potValue <= 223) {
    stepSpeed = 0.5;
  }
  else if (potValue > 223 && potValue <= 323) {
    stepSpeed = 0.75;
  }
  else if (potValue > 323 && potValue <= 423) {
    stepSpeed = 1;
  }
  else if (potValue > 423 && potValue <= 523) {
    stepSpeed = 1.25;
  }
  else if (potValue > 523 && potValue <= 623) {
    stepSpeed = 1.5;
  }
  else if (potValue > 623 && potValue <= 723) {
    stepSpeed = 1.75;
  }
  else if (potValue > 723 && potValue <= 823) {
    stepSpeed = 2;
  }
  else if (potValue > 823 && potValue <= 923) {
    stepSpeed = 2.25;
  }
  else if (potValue > 923 && potValue <= 1023) {
    stepSpeed = 2.5;
  } else {
    //nothing
  }

  //set motor speed
  myMotor->setSpeed(stepSpeed);
  Serial.print("\t");    // prints a tab
  Serial.print("STEP SPEED: ");
  Serial.print(stepSpeed);

  // read buttons
  topButtonState = digitalRead(topButtonPin);
  bottomButtonState = digitalRead(bottomButtonPin);
  Serial.print("\t");    // prints a tab
  Serial.print("TOP BUTTON: ");
  Serial.print(topButtonState);

  Serial.print("\t");    // prints a tab
  Serial.print("BOTTOM BUTTON: ");
  Serial.print(bottomButtonState);

  //checking button state
  if (topButtonState != lastTopButtonState) {
    if (topButtonState == HIGH) {
      topButtonState = HIGH;
      goDown = true;
      goUp = false;
    } else {
      topButtonState = LOW;
    }
  } else {
    //nothing
  }
  lastTopButtonState = topButtonState;

  if (bottomButtonState != lastBottomButtonState) {
    if (bottomButtonState == HIGH) {
      bottomButtonState = HIGH;
      goUp = true;
      goDown = false;
    } else {
      bottomButtonState == LOW;
    }
  } else {
    //nothing
  }
  lastBottomButtonState = bottomButtonState;

  // GO UP OR DOWN
  if (goUp == true) {
    driveDirection = FORWARD;
  } else {
    driveDirection = BACKWARD;
  }

  myMotor->step(numberOfSteps, driveDirection, DOUBLE);
  Serial.print("\t");    // prints a tab
  Serial.print("MOTOR DRIVING: ");
  Serial.print(driveDirection);
  Serial.println("");
}

