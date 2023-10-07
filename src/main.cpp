#include <Arduino.h>
#include <Wire.h>

// Motor PWM pin
#define MOTOR_PWM_PIN 3
#define PWM_STEP 10

void setup() {
  // Set motor PWM pin as output
  pinMode(MOTOR_PWM_PIN, OUTPUT);
}

void loop() {
  for (byte pwm_level = 0; pwm_level < 250; pwm_level += PWM_STEP) {
    analogWrite(MOTOR_PWM_PIN, pwm_level);
    delay(100);
  }
  for (byte pwm_level = 255; pwm_level > 0; pwm_level -= PWM_STEP) {
    analogWrite(MOTOR_PWM_PIN, pwm_level);
    delay(100);
  }
}
