#include <Arduino.h>
#include <Wire.h>

// Motor PWM pin
#define MOTOR_PWM_PIN 2

void setup() {
  Serial.begin(115200);
  // Set motor PWM pin as output
  pinMode(MOTOR_PWM_PIN, OUTPUT);
}

void loop() {
  Serial.println("Motor up");
  digitalWrite(MOTOR_PWM_PIN, HIGH);
  delay(5000);
  Serial.println("Motor down");
  digitalWrite(MOTOR_PWM_PIN, LOW);
  delay(5000);
}
