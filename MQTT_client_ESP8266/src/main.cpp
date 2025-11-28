#include <Arduino.h>
#include <PicoMQTT.h>
#include <config.h>

PicoMQTT::Client mqtt("192.168.1.104");

void setup() {
    // Usual setup
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID_WIFI, PASS_WIFI);

    // Subscribe to a topic pattern and attach a callback
    mqtt.subscribe("#", [](const char * topic, const char * payload) {
        Serial.printf("Received message in topic '%s': %s\n", topic, payload);
    });

    // Start the client
    mqtt.begin();
}

void loop() {
    // This will automatically reconnect the client if needed.  Re-subscribing to topics is never required.
    mqtt.loop();

    if (random(1000) == 0)
        mqtt.publish("picomqtt/welcome", "Hello from PicoMQTT!");
}