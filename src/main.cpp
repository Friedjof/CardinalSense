#include <SPI.h>
#include <Arduino.h>
#include <Wire.h>
#include <math.h>

#include <CardinalMotors.h>
#include <CardinalCompass.h>

#define LATCH_PIN 22
#define CLOCK_PIN 21
#define DATA_PIN 23
// Setup the I²C Address
#define VCM5883L_ADDRESS 0x0D

// Setup the I²C Pins
#define SDA_PIN 21
#define SCL_PIN 22

CardinalMotors motors(LATCH_PIN, CLOCK_PIN, DATA_PIN);
// Setup the CardinalCompass
CardinalCompass compass;

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  compass.init();
  compass.reset();
  compass.setOversampling(512);
  Serial.println("--- Starting ---");
}

void loop() {
  float angle = compass.absoluteAngle();

  Serial.print("Angle: ");
  Serial.println(angle);

  delay(100);
  for (int i = 0, j = 15; i < 16; i++, j--) {
    motors.set(i, HIGH);
    motors.set(j, HIGH);
    delay(100);
    motors.set(i, LOW);
    motors.set(j, LOW);
  }
}