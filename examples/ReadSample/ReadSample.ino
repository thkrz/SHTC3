#include <Wire.h>
#include <SHTC3.h>

void printReadings() {
  Serial.print("Temperature: ");
  Serial.print(SHTC3.getTemperature());
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(SHTC3.getHumidity());
  Serial.println(" %RH");
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  delay(3000);

  Wire.begin();
  if(!SHTC3.begin()) {
    Serial.println("SHTC3 sensor not found.");
    for (;;)
      delay(100);
  }
}

void loop() {
  Serial.println("Normal Mode, Clock Stretching Enabled, Read T First");
  SHTC3.readSample();
  printReadings();
  Serial.println();

  delay(5000);

  Serial.println("Normal Mode, Clock Stretching Disabled, Read T First");
  SHTC3.readSample(false);
  printReadings();
  Serial.println();

  delay(5000);

  Serial.println("Low Power M., Clock Stretching Enabled, Read T First");
  SHTC3.readSample(true, true);
  printReadings();
  Serial.println();

  delay(5000);

  Serial.println("Low Power M., Clock Stretching Disabled, Read T First");
  SHTC3.readSample(false, true);
  printReadings();
  Serial.println();
  Serial.println("----");

  delay(5000);
}
