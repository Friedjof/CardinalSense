#include <Arduino.h>
#include <Wire.h>
#include <math.h>

#include <CardinalCompass.h>

// Setup the I²C Address
#define VCM5883L_ADDRESS 0x0D

// Setup the I²C Pins
#define SDA_PIN 21
#define SCL_PIN 22

// Setup the CardinalCompass
CardinalCompass compass;

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  compass.init();
  compass.reset();
  compass.setOversampling(512);
}

void loop() {
  float angle = compass.absoluteAngle();

  Serial.print("Angle: ");
  Serial.println(angle);

  delay(100);
}