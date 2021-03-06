#ifndef IOT_CONFIGS_H
#define IOT_CONFIGS_H

const char* houseWiFiSsid = "scoltock";
const char* houseWiFiPassword = "nowireshere";

const char* mobileWiFiSsid = "SScoltock";
const char* mobileWiFiPassword = "scolly99";

const char* ssid = "scoltock";
const char* pass = "nowireshere";



/**
 * IoT Hub Device Connection String setup
 * Find your Device Connection String by going to your Azure portal, creating (or navigating to) an IoT Hub, 
 * navigating to IoT Devices tab on the left, and creating (or selecting an existing) IoT Device. 
 * Then click on the named Device ID, and you will have able to copy the Primary or Secondary Device Connection String to this sample.
 */
#define DEVICE_CONNECTION_STRING    "HostName=srstraininghub.azure-devices.net;DeviceId=esp1;SharedAccessKey=qJdsnbL1AY460d9x07zGLzR2PhmizH9pH0LNc2jrFms="

// The protocol you wish to use should be uncommented
//
#define SAMPLE_MQTT
//#define SAMPLE_HTTP

#endif /* IOT_CONFIGS_H */