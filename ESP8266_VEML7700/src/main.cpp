#include <Arduino.h>

#include "DFRobot_VEML7700.h"
#include <Wire.h>

#define OLED_SDA 14         // D5
#define OLED_SCL 12         // D6
/*
 * Instantiate an object to drive the sensor
 */
DFRobot_VEML7700 als;

void setup()
{
  Serial.begin(115200);
  Wire.begin(OLED_SDA,OLED_SCL);
  als.begin();   // Init
}

void loop()
{
  float lux;
  
  als.getALSLux(lux);   // Get the measured ambient light value
  Serial.print("Lux:");
  Serial.print(lux);
  Serial.println(" lx");
  
  delay(200);
}