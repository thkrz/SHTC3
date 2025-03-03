#include <Arduino.h>
#include <Wire.h>

#include "SHTC3.h"

#define I2C_ADDR 0x70

_SHTC3 SHTC3;

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

bool _recv(uint16_t *j) {
  byte buf[3];

  Wire.requestFrom(I2C_ADDR, 3, false);
  for (int i = 0; Wire.available() && i < 3; i++)
      buf[i] = Wire.read();

  if (buf[2] != _crc8(buf, 2))
    return false;

  if (j != NULL) {
    *j = buf[0];
    *j <<= 8;
    *j |= buf[1];
  }
  return true;
}

void _send(uint16_t cmd) {
  byte buf[2];

  buf[1] = cmd & 0xFF;
  buf[0] = cmd >> 8;
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(buf, 2);
  Wire.endTransmission();
}

bool _SHTC3::begin() {
  reset();
  delay(1);
  if (ready()) {
    sleep();
    return true;
  }
  return false;
}

float _SHTC3::getHumidity() {
  return _srh;
}

float _SHTC3::getTemperature() {
  return _st;
}

void _SHTC3::readSample(bool clock_stretch, bool low_power, bool rh_first) {
  const uint16_t cmd[2][4] = {
    {0x7866, 0x58E0, 0x7CA2, 0x5C24},
    {0x609C, 0x401A, 0x6458, 0x44DE}
  };

  int i = (int)low_power;
  int j = (int)rh_first;
  int k = (int)clock_stretch * 2;

  wakeup();
  delay(1);
  _send(cmd[i][j+k]);
  if (!clock_stretch)
    delay(low_power ? 2 : 20);
  uint16_t a, b;
  _recv(&a);
  _recv(&b);
  sleep();

  if (rh_first) {
    uint16_t c = b;
    b = a;
    a = c;
  }

  _st = 175.0 * a / (1<<16) - 45.0;
  _srh = 100.0 * b / (1<<16);
}

bool _SHTC3::ready() {
  _send(0xEFC8);
  return _recv(NULL);
}

void _SHTC3::reset() {
  _send(0x805D);
}

void _SHTC3::sleep() {
  _send(0xB098);
}

void _SHTC3::wakeup() {
  _send(0x3517);
}
