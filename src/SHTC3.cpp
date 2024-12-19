#include <Arduino.h>
#include <Wire.h>

#include "SHTC3.h"

#define I2C_ADDR 0x70

byte _crc8(byte data[], int len) {
  byte crc = 0xFF;

  for (int i = 0; i < len; i++) {
    crc ^= data[i];
    for (int j = 0; j < 8; j++)
      if (crc & 0x80)
        crc = (crc << 1) ^ 0x31;
      else
        crc <<= 1;
  }
  return crc;
}

uint16_t _recv() {
  byte buf[3];

  int n = Wire.requestFrom(I2C_ADDR, 3);
  for (int i = 0; i < n; i++)
    buf[i] = Wire.read();

  if (buf[2] != _crc8(buf, 2))
    return INVALID;

  uint16_t j = buf[0];
  j <<= 8;
  j |= buf[1]
  return j;
}

void _send(uint16_t cmd) {
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(cmd);
  Wire.endTransmission();
}

SHTC3::SHTC3(bool clock_stretch = true, bool low_power = false, bool rh_first = false) {
  this->clock_stretch = (int)clock_stretch * 2;
  this->low_power = (int)low_power;
  this->rh_first = (int)rh_first;
}

bool SHTC3::begin() {
  reset();
  delay(1);
  return ready();
}

float SHTC3::getHumidity() {
  return srh;
}

float SHTC3::getTemperature() {
  return st;
}

void SHTC3::readSample() {
  static const uint16_t cmd = {
    {0x7866, 0x58E0, 0x7CA2, 0x5C24},
    {0x609C, 0x401A, 0x6458, 0x44DE}
  };

  wakeup();
  delay(1);
  _send(cmd[low_power][rh_first+clock_stretch]);
  if (!clock_stretch)
    delay(low_power ? 2 : 20);
  uint16_t a = _recv();
  uint16_t b = _recv();
  sleep();

  if (rh_first) {
    uint16_t c = b;
    b = a;
    a = c;
  }

  st = 175.0 * a / (1<<16) - 45.0;
  srh = 100.0 * b / (1<<16);
}

bool SHTC3::ready() {
  _send(0xEFC8);
  return _recv() != INVALID;
}

void SHTC3::reset() {
  _send(0x805D);
}

void SHTC3::sleep() {
  _send(0xB098);
}

void SHTC3::wakeup() {
  _send(0x3517);
}
