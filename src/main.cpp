#include "Arduino.h"
#include "WiFi.h"
#include "passwords.h"

void setup() {
  Serial.begin(115200);
  // connect to WiFi
  // Try home first, then try mobile
  int ledState = HIGH;
  WiFi.setHostname("Scoltock Caravan");


  //TODO: use an array of SSID and Passwords to simply this code
  while (WiFi.status() != WL_CONNECTED)
  {
    int connectionAttempts = 5;
    WiFi.begin(houseWiFiSsid, houseWiFiPassword);

    while (WiFi.status() != WL_CONNECTED and connectionAttempts > 0) {
      delay(1000);
      digitalWrite(GPIO_NUM_2,ledState);
      Serial.println("Establishing connection to house WiFi..");
      ledState = !ledState;
      connectionAttempts--;
    }

    if (WiFi.status() == WL_CONNECTED)
      Serial.println("Connected to house WiFi");
    else
    {
      connectionAttempts = 5;
      WiFi.begin(mobileWiFiSsid, mobileWiFiPassword);
      while (WiFi.status() != WL_CONNECTED and connectionAttempts > 0) {
        delay(1000);
        digitalWrite(GPIO_NUM_2,ledState);
        Serial.println("Establishing connection to mobile WiFi..");
        ledState = !ledState;
        connectionAttempts--;
        }
    }

    if (WiFi.status() == WL_CONNECTED)
      Serial.println("Connected to mobile use WiFi");
  }
  
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());


}

void loop() {
  // put your main code here, to run repeatedly:
}