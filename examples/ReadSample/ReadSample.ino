#include <Wire.h>
#include <SHTC3.h>

SHTC3 sht;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Wire.begin();
  if(!sht.begin()) {
    Serial.println("SHTC3 sensor not found.");
    for (;;)
      delay(100);
  }
}

void loop() {
  sht.readSample();

  Serial.print("Temperature: ");
  Serial.print(sht.getTemperature());
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(sht.getHumidity());
  Serial.println(" %RH");

  delay(5000);
}
