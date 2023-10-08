#include "CardinalMotors.h"


CardinalMotors::~CardinalMotors() {
}

CardinalMotors::CardinalMotors(int latch_pin, int clock_pin, int data_pin) {
    this->latch_pin = latch_pin;
    this->clock_pin = clock_pin;
    this->data_pin = data_pin;

    pinMode(latch_pin, OUTPUT);
    pinMode(clock_pin, OUTPUT);
    pinMode(data_pin, OUTPUT);
}

void CardinalMotors::set(int pin, byte value) {
    if (value) {
        this->current_state |= (1 << pin);
    } else {
        this->current_state &= ~(1 << pin);
    }

    this->update(this->current_state);
}

void CardinalMotors::set_angle(float angle) {
    this->on(((byte) round(angle / (CIRCLE / (NUM_MOTORS - 0x01))) + CALIBRATION) % NUM_MOTORS);
}

void CardinalMotors::update(short data) {
    // Latch low
    digitalWrite(this->latch_pin, LOW);

    // Shift out the data
    this->shiftOut(data & 0xff);
    this->shiftOut((data >> 8) & 0xff);

    // Latch high
    digitalWrite(this->latch_pin, HIGH);
}

void CardinalMotors::shiftOut(byte data) {
    // MSB first
    digitalWrite(this->data_pin, LOW);
    // Clock low
    digitalWrite(this->clock_pin, LOW);

    // Shift out the bits
    for (int i = 7; i >= 0; i--) {
        digitalWrite(this->clock_pin, LOW);

        digitalWrite(this->data_pin, ~(data >> i) & 1);

        digitalWrite(this->clock_pin, HIGH);
        digitalWrite(this->data_pin, LOW);
    }

    // Clock low
    digitalWrite(this->clock_pin, LOW);
}

void CardinalMotors::on(byte pin) {
    short new_state = 0x00 | (1 << pin);

    if (new_state != this->current_state) {
        this->current_state = new_state;
        this->update(this->current_state);
    }
}

void CardinalMotors::off(byte pin) {
    short new_state = 0x00 & ~(1 << pin);

    if (new_state != this->current_state) {
        this->current_state = new_state;
        this->update(this->current_state);
    }
}