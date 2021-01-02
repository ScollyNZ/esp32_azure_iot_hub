#ifndef IOT_CONFIGS_H
#define IOT_CONFIGS_H

const char* houseWiFiSsid = "scoltock";
const char* houseWiFiPassword = "nowireshere";

const char* mobileWiFiSsid = "SScoltock";
const char* mobileWiFiPassword = "scolly99";



/**
 * IoT Hub Device Connection String setup
 * Find your Device Connection String by going to your Azure portal, creating (or navigating to) an IoT Hub, 
 * navigating to IoT Devices tab on the left, and creating (or selecting an existing) IoT Device. 
 * Then click on the named Device ID, and you will have able to copy the Primary or Secondary Device Connection String to this sample.
 */
#define DEVICE_CONNECTION_STRING    "your-iothub-DEVICE-connection-string"

// The protocol you wish to use should be uncommented
//
#define SAMPLE_MQTT
//#define SAMPLE_HTTP

#endif /* IOT_CONFIGS_H */