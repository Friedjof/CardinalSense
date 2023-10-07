#include "CardinalMotors.h"


CardinalMotors::~CardinalMotors() {
}

CardinalMotors::CardinalMotors(byte sc_pin) {
    this->sc_pin = sc_pin;
}

void CardinalMotors::init() {
    pinMode(this->sc_pin, OUTPUT);

    SPI.begin();
    SPI.setDataMode(SPI_MODE0);
    SPI.setClockDivider(SPI_CLOCK_DIV128);
    
    this->sendByte(MAX7219_REG_SCANLIMIT,   7); // show all 8 digits
    this->sendByte(MAX7219_REG_DECODEMODE,  0); // using an led matrix (not digits)
    this->sendByte(MAX7219_REG_DISPLAYTEST, 0); // no display test
    this->sendByte(MAX7219_REG_INTENSITY,   0); // character intensity: range: 0 to 15
    this->sendByte(MAX7219_REG_SHUTDOWN,    1); // not in shutdown mode (ie. start it up)
}

void CardinalMotors::sendByte(const byte reg, const byte data) {
    // enable the line
    digitalWrite(this->sc_pin, LOW);

    // now shift out the data
    SPI.transfer (reg);
    SPI.transfer (data);

    digitalWrite(this->sc_pin, HIGH);
}

void CardinalMotors::setIntensity(const byte intensity) {
    this->sendByte(MAX7219_REG_INTENSITY, intensity);
}