#pragma once
/*
  Library for controlling the Cardinal Motors (Vibration Motors)
  Because of the high number of motors (16), we need to use the IC 74HC595
*/

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#define CIRCLE 360
#define NUM_MOTORS 16
#define CALIBRATION 5
#define I2C_START_ADDRESS 0x20
#define I2C_MODULES 8

class CardinalMotors {
  private:
    int sda_pin;
    int scl_pin;

    short c_state = 0x0000;

    void send_state_to_module(byte module, byte state);
    byte calc_module(byte pin);

  public:
    ~CardinalMotors();
    CardinalMotors(int sda_pin, int scl_pin);

    void begin();

    void set(byte pin, bool value);

    void set_angle(float angle);
};