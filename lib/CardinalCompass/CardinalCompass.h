#ifndef CARDINAL_COMPASS_H
#define CARDINAL_COMPASS_H

#include <Arduino.h>
#include <Wire.h>
#include <math.h>

class CardinalCompass {
public:
  void init();
  void reset();
  int  ready();
  void reconfig();

  float absoluteAngle();

  int readRaw( int16_t *x, int16_t *y, int16_t *z, int16_t *t );

  void setSamplingRate( int rate );
  void setRange( int range );
  void setOversampling( int ovl );

private:
  uint8_t addr;
  uint8_t mode;
  uint8_t rate;
  uint8_t range;
  uint8_t oversampling;
};

#endif