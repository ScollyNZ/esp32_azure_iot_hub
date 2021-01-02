#include "Arduino.h"
#include "WiFi.h"
#include "passwords.h"
#include "Wire.h"
#include "ADS1115.h"

void scanPorts();
void check_if_exist_I2C();

ADS1115 adc0(ADS1115_ADDRESS_ADDR_GND); 

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

    if (WiFi.status() == WL_CONNECTED)
      Serial.println("Connected to mobile use WiFi");
    }

  }
  
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Wire.begin(25,26);
  Serial.println("Initializing I2C devices..."); 
  adc0.initialize(); // initialize ADS1115 16 bit A/D chip
    
  Serial.println("Testing device connections...");
  //TODO: fail at this point
  Serial.println(adc0.testConnection() ? "ADS1115 connection successful" : "ADS1115 connection failed");

  adc0.setMode(ADS1115_MODE_CONTINUOUS);
}

void loop() {
    adc0.setGain(ADS1115_PGA_4P096);

    while(true) {
      float readingVolts=adc0.getConversionP0GND()*adc0.getMvPerCount();
      Serial.println(readingVolts);
      delay(500);
    }



}

