#include <Arduino.h>

#include "Adafruit_VL53L0X.h"
#include <ESP8266WiFi.h>

#define OLED_SDA 14         // D6
#define OLED_SCL 12         // D

Adafruit_VL53L0X lox = Adafruit_VL53L0X();


void setup() {
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  Wire.begin(OLED_SDA,OLED_SCL);

  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }

}

void loop()
{
  VL53L0X_RangingMeasurementData_t measure;

  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
      Serial.print(measure.RangeMilliMeter);
      Serial.println("mm");
      delay(50);
  } else {
    return;
  }
}