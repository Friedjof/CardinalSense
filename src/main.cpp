#include <SPI.h>
#include <CardinalMotors.h>

#define LATCH_PIN 22
#define CLOCK_PIN 21
#define DATA_PIN 23


CardinalMotors motors(LATCH_PIN, CLOCK_PIN, DATA_PIN);

void setup() {
  Serial.begin(115200);

  Serial.println("--- Starting ---");
}

void loop() {
  for (int i = 0, j = 15; i < 16; i++, j--) {
    motors.set(i, HIGH);
    motors.set(j, HIGH);
    delay(100);
    motors.set(i, LOW);
    motors.set(j, LOW);
  }
}