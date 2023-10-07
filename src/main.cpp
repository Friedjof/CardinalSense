#include <SPI.h>
#include <CardinalMotors.h>

#define NUMBER_OF_DEVICES 1
#define CS_PIN 21

CardinalMotors motors(CS_PIN);

void setup() {
    motors.init();
    motors.setIntensity(0);
}

void loop() {
  for (int i = 1; i <= 8; i++) {
    for (int j = 0; j < 8; j++) {
      motors.sendByte(i, 0x01 << j);
      delay(100);
    }
  }
}