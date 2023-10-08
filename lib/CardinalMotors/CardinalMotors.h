/*
  Library for controlling the Cardinal Motors (Vibration Motors)
  Because of the high number of motors (16), we need to use the IC 74HC595
*/

#ifndef __DEFINED_CARDINALMOTORS_H__
#define __DEFINED_CARDINALMOTORS_H__

#include <Arduino.h>
#include <SPI.h>

#define CIRCLE 360
#define NUM_MOTORS 16
#define CALIBRATION 5

class CardinalMotors {
private:
    int latch_pin;
    int clock_pin;
    int data_pin;

    // 16 bits for 16 motors
    short current_state;
public:
    ~CardinalMotors();
    CardinalMotors(int latch_pin, int clock_pin, int data_pin);

    void set(int pin, byte value);
    void set_angle(float angle);
    void update(short data);
    void shiftOut(byte data);

    void on(byte pin);
    void off(byte pin);
};
#endif