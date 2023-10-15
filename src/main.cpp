#include <Arduino.h>

#include <math.h>

#include <CardinalMotors.h>
#include <CardinalCompass.h>

// Setup the I²C Pins
#define SDA_PIN 18
#define SCL_PIN 17

// Setup CardinalMotors and CardinalCompass
CardinalMotors motors(SDA_PIN, SCL_PIN);
CardinalCompass compass;

void setup() {
  // Setup the motors
  motors.begin();
  // Setup the compass
  compass.begin();
}

void loop() {
  // Read the compass
  float angle = compass.heading();

  // Set the motor to the angle
  motors.set_angle(angle);
}