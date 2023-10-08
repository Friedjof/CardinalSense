#include <Arduino.h>

#include <Wire.h>
#include <math.h>

#include <CardinalMotors.h>
#include <CardinalCompass.h>

// Setup the Motors
#define LATCH_PIN 22
#define CLOCK_PIN 21
#define DATA_PIN  23

// Setup the I²C Pins
#define SDA_PIN   18
#define SCL_PIN   17

// Setup CardinalMotors and CardinalCompass
CardinalMotors  motors(LATCH_PIN, CLOCK_PIN, DATA_PIN);
CardinalCompass compass;

void setup() {
  // Set I²C pins
  Wire.begin(SDA_PIN, SCL_PIN);

  // 
  compass.init();
}

void loop() {
  // Read the compass
  float angle = compass.heading();

  // Set the motor to the angle
  motors.set_angle(angle);
}