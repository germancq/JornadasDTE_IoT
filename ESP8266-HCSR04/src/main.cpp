#include <Arduino.h>

#include <HCSR04.h>



UltraSonicDistanceSensor distanceSensor(D7, D8);  // Initialize sensor that uses digital pins 13 and 12.

void setup () {
    Serial.begin(115200);  // We initialize serial connection so that we could print values from sensor.
}

void loop () {
    // Every 1 second, do a measurement using the sensor and print the distance in centimeters.
    double distance = distanceSensor.measureDistanceCm();

    Serial.print(distance);
    Serial.println(F("cm"));
    delay(1000);
}