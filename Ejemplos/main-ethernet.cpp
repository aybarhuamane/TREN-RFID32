#include <Arduino.h>
#include <SPI.h>
#include <EthernetENC.h>
#include "PubSubClient.h"

extern SPIClass RED;


#define SS_PIN_H 5
#define CLK_PIN_H 18
#define MOSI_PIN_H 23
#define MISO_PIN_H 19



/*
MOSI = 23;
MISO = 19;
SCK = 18;
y el CS predeterminado es 5
*/

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

char server[] = "www.google.com";    // name address for Google (using DNS)
#define CLIENT_ID       "JEZIEL_78233"
#define INTERVAL        3000 // 3 sec delay between publishing

// IPAddress ip(192, 168, 1, 18);
// IPAddress myDns(192, 168, 1, 1);

IPAddress ip(172, 19, 34, 17); //172.19.34.17
IPAddress myDns(172,19,34,1); //  172.19.34.1

// MQTT
#define SERVER "iotx.cloux.site"
const char *mqtt_user = "adminx"; // ssid de la red
const char *mqtt_pass = "adminx"; // contraseña de la red
String clientIds = "pablo";
//mqtt

#define port 1883
#define TOPICO_RAIZ "data/"
#define TOPICO_DATA1 TOPICO_RAIZ "asa"
#define TOPICO_DATA2 TOPICO_RAIZ "asa"



EthernetClient client;
PubSubClient mqttClient;
long previousMillis;

unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
bool printWebData = true;  // set to false for better speed measurement



void sendData(void);


void setup() {

  Serial.begin(115200);
  // RED.begin(CLK_PIN_H, MISO_PIN_H, MOSI_PIN_H, SS_PIN_H); // //CLK,MISO,MOIS,SS.
  // RED.begin(SS_PIN_H, OUTPUT);



  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Ethernet.init(33); 
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
   mqttClient.setClient(client);
   mqttClient.setServer(SERVER,1883);
   Serial.println(F("MQTT client configured"));
previousMillis = millis();
  // give the Ethernet shield a second to initialize:
 

  // if you get a connection, report back via serial:

  beginMicros = micros();
}

void loop() {

   auto link = Ethernet.linkStatus();
  Serial.print("Link status: ");
  switch (link) {
    case Unknown:
      Serial.println("Unknown");
      break;
    case LinkON:
      Serial.println("ON");
      break;
    case LinkOFF:
      Serial.println("OFF");
      break;
  }
  delay(1000);

   if(millis() - previousMillis > INTERVAL) {
    sendData();
    previousMillis = millis();
  }
  mqttClient.loop();
}

void sendData() {

  Serial.print("Attempting connecting server..");
  // Create a random client ID
  String clientId = "device";
  clientId += String(random(0xffff), HEX);
 
  if(mqttClient.connect(clientId.c_str(),mqtt_user, mqtt_pass)) {
   mqttClient.publish(TOPICO_DATA1, "hola_esp32");
    Serial.println("Enviado... ");
    mqttClient.subscribe(TOPICO_DATA1);
 }
  else
  {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      ESP.restart();
  }
}