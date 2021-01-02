#include "Arduino.h"
#include "WiFi.h"
#include "passwords.h"
#include "Wire.h"
#include "ADS1115.h"

void scanPorts();
void check_if_exist_I2C();

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

  scanPorts();
}

void loop() {
  
}

uint8_t portArray[] = {25,26};
String portMap[] = {"GPIO25", "GPIO26"};

void scanPorts() { 
  for (uint8_t i = 0; i < sizeof(portArray); i++) {
    for (uint8_t j = 0; j < sizeof(portArray); j++) {
      if (i != j){
        Serial.print("Scanning (SDA : SCL) - " + portMap[i] + " : " + portMap[j] + " - ");
        Wire.begin(portArray[i], portArray[j]);
        check_if_exist_I2C();
      }
    }
  }
}

void check_if_exist_I2C() {
  byte error, address;
  int nDevices;
  nDevices = 0;
  for (address = 1; address < 127; address++ )  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0){
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknow error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  } //for loop
  if (nDevices == 0)
    Serial.println("No I2C devices found");
  else
    Serial.println("**********************************\n");
  //delay(1000);           // wait 1 seconds for next scan, did not find it necessary
}