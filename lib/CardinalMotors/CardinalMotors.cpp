#include "CardinalMotors.h"


CardinalMotors::~CardinalMotors() { }

CardinalMotors::CardinalMotors(int sda_pin, int scl_pin) {
  this->sda_pin = sda_pin;
  this->scl_pin = scl_pin;
}

void CardinalMotors::begin() {
  // start the I²C bus
  Wire.begin(this->sda_pin, this->scl_pin);
  
  for (int i = 0; i < I2C_MODULES; i++) {
    // Send the state to the module
    this->send_state_to_module(I2C_START_ADDRESS + i, 0x00);
  }
}

byte CardinalMotors::calc_module(byte pin) {
  // Calculate the module
  return (pin - (pin % 0x02)) / 0x02;
}

void CardinalMotors::send_state_to_module(byte module, byte state) {
  // Send the state to the module
  byte address = I2C_START_ADDRESS + module;

  // Send the state to the module
  Wire.beginTransmission(address);
  Wire.write(state);
  Wire.endTransmission();
}

void CardinalMotors::set(byte pin, bool value) {
  // Set the pin to the value
  byte module = this->calc_module(pin);

  // Calculate the new state
  short n_state = this->c_state;

  if (value) {
    n_state |= (0x01 << pin);
  } else {
    n_state &= ~(0x01 << pin);
  }

  // Save the new state
  this->c_state = n_state;

  // Send the new state to the module
  byte v = (n_state >> (module * 0x02)) & 0x03;

  this->send_state_to_module(module, v);
}

void CardinalMotors::set_angle(float angle) {
  // Set the motors to the angle
  float step = CIRCLE / NUM_MOTORS;

  int motor = (int) (angle / step);

  // Set the motors
  for (int i = 0; i < NUM_MOTORS; i++) {
    if (i == motor) {
      this->set(i, true);
    } else {
      this->set(i, false);
    }
  }
}