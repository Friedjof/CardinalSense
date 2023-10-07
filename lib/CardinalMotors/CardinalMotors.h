#ifndef __DEFINED_CARDINALMOTORS_H__
#define __DEFINED_CARDINALMOTORS_H__

#include <Arduino.h>
#include <SPI.h>


// max7219 registers
#define MAX7219_REG_NOOP         0x0
#define MAX7219_REG_DIGIT0       0x1
#define MAX7219_REG_DIGIT1       0x2
#define MAX7219_REG_DIGIT2       0x3
#define MAX7219_REG_DIGIT3       0x4
#define MAX7219_REG_DIGIT4       0x5
#define MAX7219_REG_DIGIT5       0x6
#define MAX7219_REG_DIGIT6       0x7
#define MAX7219_REG_DIGIT7       0x8
#define MAX7219_REG_DECODEMODE   0x9
#define MAX7219_REG_INTENSITY    0xA
#define MAX7219_REG_SCANLIMIT    0xB
#define MAX7219_REG_SHUTDOWN     0xC
#define MAX7219_REG_DISPLAYTEST  0xF


class CardinalMotors
{
private:
    byte sc_pin;
public:
    ~CardinalMotors();
    CardinalMotors(byte sc_pin);

    /**
     * Initializes the SPI interface
     */
    void init();
    
    /**
     * Sets the intensity on all devices.
     * intensity: 0-15
     */
    void setIntensity(byte intensity);

    /**
     * Send a byte to a specific device.
     */
    void sendByte(const byte reg, const byte data);
};
#endif