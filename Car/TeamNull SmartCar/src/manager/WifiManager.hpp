#ifndef WiFiManager_H_   /* Include guard */
#define WiFiManager_H_

#include "WiFi.h" // ESP32 WiFi include

void connectToWiFi(char* SSID, char* password);
void getInstructionsFromServer();
#endif // WiFiManager_H_