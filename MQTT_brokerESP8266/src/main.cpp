#include <Arduino.h>
#include <PicoMQTT.h>
//#include <uMQTTBroker.h>
#include <config.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1   // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // If not work please scan the bus
#define OLED_SDA 14         // D6
#define OLED_SCL 12         // D5

Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire);

PicoMQTT::Server broker_mqtt;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID_WIFI,PASS_WIFI);
  Serial.print("Conectando a:\t");
  Serial.println(SSID_WIFI);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(200);
    Serial.print('.');
  }
  Serial.println();
  Serial.print("Conectado a:\t");
  Serial.println(WiFi.SSID()); 
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
  
  Wire.begin(OLED_SDA, OLED_SCL);
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("IP del dispositivo:");
  display.println(WiFi.localIP());
  display.display();

  Serial.setDebugOutput(true);

  // Start the broker
  broker_mqtt.begin();

  Serial.println("END SETUP");
}

void loop() {
  // put your main code here, to run repeatedly:
  broker_mqtt.loop();
}