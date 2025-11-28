#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>


// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  String d;
  bool e;
} struct_message;

struct_message myData;
struct_message incomingData;

//MAC address
uint8_t destinationAddress [] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

unsigned long lastTime = 0;  
unsigned long timerDelay = 10000;  // send readings timer

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus){
  Serial.println("----");
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}

void OnDataRcv(uint8_t *mac_addr, uint8_t *incoming_data, uint8_t len){
  Serial.println("Data Received");
  memcpy(&incomingData, incoming_data, len);
  Serial.println("String recibido:");
  Serial.println(incomingData.d);
  Serial.print("Random_number: ");
  Serial.println(incomingData.b);
  Serial.println("End Data Received");
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  Serial.print("ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRcv);
  esp_now_add_peer(destinationAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
}
 
void loop() {
  if ((millis() - lastTime) > timerDelay) {
    // Set values to send
    strcpy(myData.a, "THIS IS A CHAR");
    myData.b = random(1,20);
    myData.c = 1.2;
    myData.d = "Hello";
    myData.e = false;

    // Send message via ESP-NOW
    esp_now_send(destinationAddress, (uint8_t *) &myData, sizeof(myData));
    lastTime = millis();
  }
}