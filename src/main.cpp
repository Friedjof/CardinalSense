#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

#define VIBRATION_MOTORS 16

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345); // Du kannst hier jede beliebige I2C-Adresse verwenden

const int motorPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};

void setup() {
  Serial.begin(115200);
  Serial.println("Magnetometer-Beispiel");

  if(!mag.begin()) {
    Serial.println("Das Magnetometer konnte nicht gefunden werden. Bitte überprüfe deine Verkabelung.");
    while(1);
  }

  mag.setMagGain(HMC5883_MAGGAIN_1_3);
  mag.enableAutoRange(true);

  for (int i = 0; i < 16; i++) {
    pinMode(motorPins[i], OUTPUT);
    digitalWrite(motorPins[i], LOW);
  }
}

void loop() {
  sensors_event_t event;
  mag.getEvent(&event);

  float heading = atan2(event.magnetic.x, event.magnetic.y);
  if (heading < 0) heading += 2 * PI;
  float headingDegrees = heading * 180 / M_PI;

  int motorIndex = int(headingDegrees / 360 * VIBRATION_MOTORS) % VIBRATION_MOTORS;

  for (int i = 0; i < 16; i++) {
    digitalWrite(motorPins[i], LOW);
  }

  digitalWrite(motorPins[motorIndex], HIGH);

  Serial.print("Richtung (Azimut): ");
  Serial.print(headingDegrees);
  Serial.println(" Grad");

  delay(1000);
}
