#ifndef EAH_h
#define EAH_h
#include <stdint.h>
#include <Arduino.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <PubSubClient.h>

#endif



class EAH
{

private:
    /* data */
public:

#define RST_PIN 15
#define SS_PIN 21
// WIFI
const char *ssid = "Wifi_Comedor";
const char *password = "movistar123";

// MQTT
const char *mqtt_server = "proyect.cloux.site";
const char *mqtt_user = "adminx"; // ssid de la red
const char *mqtt_pass = "adminx"; // contraseña de la red
String clientIds = "pablo";

#define port 1883
#define TOPICO_RAIZ "data/"
#define TOPICO_DATA1 TOPICO_RAIZ "asa"
#define TOPICO_DATA2 TOPICO_RAIZ "asa"

// OTROS
String hostname = "lector-wifi";

void setup_wifi(const char *ssid, const char *password);
void callback(char *topic, byte *payload, unsigned int length);
void reconnect(String nameID);
void setup_mqtt();
void loop_mqtt(String nameID);

void loop_iot(String clientId,const char *mqtt_users,const char *mqtt_passs);

};