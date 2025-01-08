#include <Wire.h>
#include <SHTC3.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Wire.begin();
  if(!SHTC3.begin()) {
    Serial.println("SHTC3 sensor not found.");
    for (;;)
      delay(100);
  }
}

void loop() {
  SHTC3.readSample();

  Serial.print("Temperature: ");
  Serial.print(SHTC3.getTemperature());
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(SHTC3.getHumidity());
  Serial.println(" %RH");

  delay(5000);
}
