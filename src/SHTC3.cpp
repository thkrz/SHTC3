#include <Arduino.h>
#include <Wire.h>

#include "SHTC3.h"

#define I2C_ADDR 0x70

uint16_t cmd;

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
    return 0;

  uint16_t j = buf[0];
  j <<= 8;
  j |= buf[1]
  return j;
}

void _send() {
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
  static const uint16_t mc = {
    {0x7866, 0x58E0, 0x7CA2, 0x5C24},
    {0x609C, 0x401A, 0x6458, 0x44DE}
  };

  wakeup();
  cmd = mc[low_power][rh_first+clock_stretch]
  _send();
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

  st = 175.0 * st / (1<<16) - 45.0;
  srh = 100.0 * srh / (1<<16);
}

bool SHTC3::ready() {
  cmd = 0xEFC8;
  _send();
  return _recv() > 0;
}

void SHTC3::reset() {
  cmd = 0x805D;
  _send();
}

void SHTC3::sleep() {
  cmd = 0xB098;
  _send();
}

void SHTC3::wakeup() {
  cmd = 0x3517;
  _send();
  delay(1);
}
