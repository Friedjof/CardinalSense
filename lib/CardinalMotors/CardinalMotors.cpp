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

void CardinalMotors::update(short data) {
    digitalWrite(this->latch_pin, LOW);
    digitalWrite(this->data_pin, LOW);
    digitalWrite(this->clock_pin, LOW);

    this->shiftOut(data & 0xff);
    this->shiftOut((data >> 8) & 0xff);

    digitalWrite(this->clock_pin, LOW);
    digitalWrite(this->latch_pin, HIGH);
}

void CardinalMotors::shiftOut(byte data) {
    digitalWrite(this->data_pin, LOW);
    digitalWrite(this->clock_pin, LOW);

    for (int i = 7; i >= 0; i--) {
        digitalWrite(this->clock_pin, LOW);

        digitalWrite(this->data_pin, ~(data >> i) & 1);

        digitalWrite(this->clock_pin, HIGH);
        digitalWrite(this->data_pin, LOW);
    }

    digitalWrite(this->clock_pin, LOW);
}