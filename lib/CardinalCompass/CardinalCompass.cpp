#include "CardinalCompass.h"

/*
 * QMC5883L
 * http://wiki.epalsite.com/images/7/72/QMC5883L-Datasheet-1.0.pdf
 */

/* The default I2C address of this chip */
#define CARDINAL_COMPASS_ADDR 0x0D

/* Register numbers */
#define CARDINAL_COMPASS_X_LSB 0
#define CARDINAL_COMPASS_X_MSB 1
#define CARDINAL_COMPASS_Y_LSB 2
#define CARDINAL_COMPASS_Y_MSB 3
#define CARDINAL_COMPASS_Z_LSB 4
#define CARDINAL_COMPASS_Z_MSB 5
#define CARDINAL_COMPASS_STATUS 6
#define CARDINAL_COMPASS_TEMP_LSB 7
#define CARDINAL_COMPASS_TEMP_MSB 8
#define CARDINAL_COMPASS_CONFIG 9
#define CARDINAL_COMPASS_CONFIG2 10
#define CARDINAL_COMPASS_RESET 11
#define CARDINAL_COMPASS_RESERVED 12
#define CARDINAL_COMPASS_CHIP_ID 13

/* Bit values for the STATUS register */
#define CARDINAL_COMPASS_STATUS_DRDY 1
#define CARDINAL_COMPASS_STATUS_OVL 2
#define CARDINAL_COMPASS_STATUS_DOR 4

/* Oversampling values for the CONFIG register */
#define CARDINAL_COMPASS_CONFIG_OS512 0b00000000
#define CARDINAL_COMPASS_CONFIG_OS256 0b01000000
#define CARDINAL_COMPASS_CONFIG_OS128 0b10000000
#define CARDINAL_COMPASS_CONFIG_OS64  0b11000000

/* Range values for the CONFIG register */
#define CARDINAL_COMPASS_CONFIG_2GAUSS 0b00000000
#define CARDINAL_COMPASS_CONFIG_8GAUSS 0b00010000

/* Rate values for the CONFIG register */
#define CARDINAL_COMPASS_CONFIG_10HZ   0b00000000
#define CARDINAL_COMPASS_CONFIG_50HZ   0b00000100
#define CARDINAL_COMPASS_CONFIG_100HZ  0b00001000
#define CARDINAL_COMPASS_CONFIG_200HZ  0b00001100

/* Mode values for the CONFIG register */
#define CARDINAL_COMPASS_CONFIG_STANDBY 0b00000000
#define CARDINAL_COMPASS_CONFIG_CONT    0b00000001

/* Apparently M_PI isn't available in all environments. */
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

static void write_register( int addr, int reg, int value ) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

static int read_register( int addr, int reg, int count ) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.endTransmission();
  
  Wire.requestFrom(addr,count);
  int n = Wire.available();
  if(n!=count) return 0;

  return n;
}

void CardinalCompass::reconfig() {
  write_register(addr,CARDINAL_COMPASS_CONFIG,oversampling|range|rate|mode);  
}

void CardinalCompass::reset() {
  write_register(addr,CARDINAL_COMPASS_RESET,0x01);
  this->reconfig();
}

/*
  Set the oversampling rate. Higher values give better
  resolution but take longer to complete.
*/
void CardinalCompass::setOversampling( int x ) {
  switch(x) {
    case 512:
      oversampling = CARDINAL_COMPASS_CONFIG_OS512;
      break;
    case 256:
      oversampling = CARDINAL_COMPASS_CONFIG_OS256;
      break;
    case 128:
      oversampling = CARDINAL_COMPASS_CONFIG_OS128;
      break;
    case 64:
      oversampling = CARDINAL_COMPASS_CONFIG_OS64;
      break;
  } 
  this->reconfig();
}

void CardinalCompass::setRange( int x ) {
  switch(x) {
    case 2:
      range = CARDINAL_COMPASS_CONFIG_2GAUSS;
      break;
    case 8:
      range = CARDINAL_COMPASS_CONFIG_8GAUSS;
      break;
  }
  this->reconfig();
}

void CardinalCompass::setSamplingRate( int x ) {
  switch(x) {
    case 10:
      rate = CARDINAL_COMPASS_CONFIG_10HZ;
      break;
    case 50:
      rate = CARDINAL_COMPASS_CONFIG_50HZ;
      break;
    case 100:
      rate = CARDINAL_COMPASS_CONFIG_100HZ;
      break;
    case 200:
      rate = CARDINAL_COMPASS_CONFIG_200HZ;
      break;
  }
  this->reconfig();
}

void CardinalCompass::begin() {
  /* This assumes the wire library has been initialized. */
  addr = CARDINAL_COMPASS_ADDR;
  oversampling = CARDINAL_COMPASS_CONFIG_OS512;
  range = CARDINAL_COMPASS_CONFIG_2GAUSS;
  rate = CARDINAL_COMPASS_CONFIG_50HZ;
  mode = CARDINAL_COMPASS_CONFIG_CONT;
  this->reset();
}

int CardinalCompass::ready() {
  if(!read_register(addr,CARDINAL_COMPASS_STATUS,1)) return 0;
  uint8_t status = Wire.read();
  return status & CARDINAL_COMPASS_STATUS_DRDY; 
}

/*
  Read the raw values from the sensor.
  @param
    - x: the x value
    - y: the y value
    - z: the z value
    - t: the temperature
*/
int CardinalCompass::readRaw( int16_t *x, int16_t *y, int16_t *z, int16_t *t ) {
  while(!ready()) {}

  if(!read_register(addr,CARDINAL_COMPASS_X_LSB,6)) return 0;

  *x = Wire.read() | (Wire.read()<<8);
  *y = Wire.read() | (Wire.read()<<8);
  *z = Wire.read() | (Wire.read()<<8);

  return 1;
}

float CardinalCompass::heading(){
  int16_t x, y, z, t;

  if(!readRaw(&x,&y,&z,&t)) return 0;

  /* Update the observed boundaries of the measurements */

  if(x < this->xlow) this->xlow = x;
  if(x > this->xhigh) this->xhigh = x;
  if(y < this->ylow) this->ylow = y;
  if(y > this->yhigh) this->yhigh = y;

  /* Bail out if not enough data is available. */
  
  if( this->xlow == this->xhigh || this->ylow == this->yhigh ) return 0;

  /* Recenter the measurement by subtracting the average */

  x -= (this->xhigh + this->xlow)/2;
  y -= (this->yhigh + this->ylow)/2;

  /* Rescale the measurement to the range observed. */
  
  float fx = (float)x / (this->xhigh - this->xlow);
  float fy = (float)y / (this->yhigh - this->ylow);

  float heading = 180.0 * atan2(fy, fx) / M_PI;
  if(heading <= 0) heading += 360;
  
  return heading;
}