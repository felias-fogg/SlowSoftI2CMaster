/* Arduino Slow Software I2C Master */

#include <SlowSoftI2CMaster.h>

SlowSoftI2CMaster::SlowSoftI2CMaster(uint8_t sda, uint8_t scl) {
  _sda = sda;
  _scl = scl;
}

// Init function. Needs to be called once in the beginning.
// Returns false if SDA or SCL are low, which probably means 
// a I2C bus lockup or that the lines are not pulled up.
bool SlowSoftI2CMaster::i2c_init(void) {
  pinMode(_sda, INPUT);
  pinMode(_scl, INPUT);
  if (digitalRead(_sda) == LOW || digitalRead(_scl) == LOW) return false;
  pinMode(_sda, OUTPUT);
  digitalWrite(_sda, HIGH);
  pinMode(_scl, OUTPUT);
  digitalWrite(_scl, HIGH);
  return true;
}

// Start transfer function: <addr> is the 8-bit I2C address (including the R/W
// bit). 
// Return: true if the slave replies with an "acknowledge", false otherwise
bool SlowSoftI2CMaster::i2c_start(uint8_t addr) {
  digitalWrite(_sda, LOW);
  delayMicroseconds(DELAY);
  digitalWrite(_scl, LOW);
  return i2c_write(addr);
}

// Repeated start function: After having claimed the bus with a start condition,
// you can address another or the same chip again without an intervening 
// stop condition.
// Return: true if the slave replies with an "acknowledge", false otherwise
bool SlowSoftI2CMaster::i2c_rep_start(uint8_t addr) {
  digitalWrite(_sda, HIGH);
  digitalWrite(_scl, HIGH);
  delayMicroseconds(DELAY);
  return i2c_start(addr);
}

// Issue a stop condition, freeing the bus.
void SlowSoftI2CMaster::i2c_stop(void) {
  digitalWrite(_sda, LOW);
  delayMicroseconds(DELAY);
  digitalWrite(_scl, HIGH);
  delayMicroseconds(DELAY);
  digitalWrite(_sda, HIGH);
  delayMicroseconds(DELAY);
}

// Write one byte to the slave chip that had been addressed
// by the previous start call. <value> is the byte to be sent.
// Return: true if the slave replies with an "acknowledge", false otherwise
bool SlowSoftI2CMaster::i2c_write(uint8_t value) {
  for (uint8_t m = 0X80; m != 0; m >>= 1) {
    digitalWrite(_sda, m & value);
    digitalWrite(_scl, HIGH);
    delayMicroseconds(DELAY);
    digitalWrite(_scl, LOW);
  }
  // get Ack or Nak
  pinMode(_sda, INPUT);
  digitalWrite(_sda, HIGH);
  digitalWrite(_scl, HIGH);
  uint8_t rtn = digitalRead(_sda);
  digitalWrite(_scl, LOW);
  pinMode(_sda, OUTPUT);
  digitalWrite(_sda, LOW);
  return rtn == 0;
}

// Read one byte. If <last> is true, we send a NAK after having received 
// the byte in order to terminate the read sequence. 
uint8_t SlowSoftI2CMaster::i2c_read(bool last) {
  uint8_t b = 0;
  digitalWrite(_sda, HIGH);
  pinMode(_sda, INPUT);
  for (uint8_t i = 0; i < 8; i++) {
    b <<= 1;
    delayMicroseconds(DELAY);
    digitalWrite(_scl, HIGH);
    if (digitalRead(_sda)) b |= 1;
    digitalWrite(_scl, LOW);
  }
  pinMode(_sda, OUTPUT);
  digitalWrite(_sda, last);
  digitalWrite(_scl, HIGH);
  delayMicroseconds(DELAY);
  digitalWrite(_scl, LOW);
  digitalWrite(_sda, LOW);
  return b;
}
