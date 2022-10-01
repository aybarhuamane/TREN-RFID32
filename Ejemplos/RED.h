#include <Arduino.h>
#include <SPI.h>
#include <EthernetENC.h>
#include "PubSubClient.h"

// ETHERNET
//byte mac[] = {0x30, 0x2B, 0x2D, 0x35, 0x51, 0xA2};
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//byte mac[] = {0xFF, 0xFF, 0xFF , 0xFF, 0x00};    
// byte mac[] = {0x01,0x02,0x03,0x04, 0x05} ;      
//byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 
//char server[] = "www.google.com"; // name address for Google (using DNS)
//IPAddress ip(192, 168, 1, 17);  //

// IPAddress ip(10, 10, 0, 51);
// IPAddress myDns(10,10,0,1); 
IPAddress ip(172, 19, 34,250); //172.19.34.17 - 250
IPAddress myDns(172,24,34,1); //  172.19.34.1


//  172.19.34.1 puerta de enlace 

// 
// DNS :172.24.20.198
// 172.24.20.31

//IPAddress myDns(192, 168, 1, 1); //

// MQTT
EthernetClient espClient;
PubSubClient client(espClient);
//PubSubClient mqttClient;
//#define SERVER "iotx.cloux.site"
#define PORT 1883;

//const char *mqtt_server = "proyect.cloux.site";
const char *mqtt_server = "172.19.34.17"
const char *mqtt_user = "adminx"; // Credentials mqtt user
const char *mqtt_pass = "adminx"; // Credentials mqtt pass
String clientId = "device_rfid";

 // MQTT TOPIC

#define TOPICO_RAIZ "data/"
#define TOPICO_PUB_DATA1 TOPICO_RAIZ "encontrado"
#define TOPICO_SUB_DATA1 TOPICO_PUB_DATA1

#define TOPICO_PUB_DATA2 TOPICO_RAIZ "buscar2"
#define TOPICO_SUB_DATA2 TOPICO_PUB_DATA2

//MILLS
long previousMillis;
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
#define INTERVAL 3000 // 3 sec delay between publishing
int incremento =0;
//ENDMILLS

#if defined _CONFIG3
        // RED : _CONFIG3
        /*
        MOSI = 23;
        MISO = 19;
        SCK = 18;
        y el CS predeterminado es 5 pero no es recomedable usar porque el pin es invertido cuando esta enlow se envia un high
        usamos Ethernet.init(15);
        */
#endif


void sendData() {

  Serial.print("Attempting connecting server..");
  // Create a random client ID
  clientId += String(random(0xffff), HEX);
 
  if(client.connect(clientId.c_str(),mqtt_user, mqtt_pass)) {
   client.publish(TOPICO_PUB_DATA1, "hola_esp32");
    Serial.println("Enviado... ");
    client.subscribe(TOPICO_PUB_DATA1);
 }
  else
  {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      ESP.restart();
  }
}

void reconnect() {

  while (!client.connected()) {

    Serial.println("Intentando conexion MQTT");//Imprime cadena
    clientId = clientId + String(random(0xffff), HEX);//Genera una cadena con valor random

    //if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass)) {
      if (client.connect(clientId.c_str())){
      Serial.println("Conexion a MQTT exitosa!!");//Imprime cadena
      print_lcdc("SERVER CONNECTED !");
      // INDICA CONEXION MQTT EXITOSA
      parpadeo(false); 
      client.subscribe(TOPICO_SUB_DATA1);//Suscripcion a topico
      client.subscribe(TOPICO_SUB_DATA2);
      //client.publish(TOPICO_PUB_DATA1, "BIEVENIDO");

    } else {
      Serial.print("Fallo la conexion ");//Imprime cadena
      Serial.println(client.state());//Imprime error de la conexion
      Serial.print(" Se intentara denuevo en 5 segundos");//Imprime cadena

      //delay(2000);//Espera 2 segundos para seguir intentando conectarse 
      incremento+=1;   //-> se movio al indicador.h

      print_lcd("Reconnecting..");
      parpadeo(true); // parpadea el indicador
      delay(2000);
     if (incremento > 5){
      Serial.println("\nReiniciando por fallo MQTT SERVER...");
        ESP.restart();
        
     }
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Path -> ");//Imprime cadena
  Serial.print(topic);//Imprime puntero topic, que apunta a una cadena
  Serial.print("\n");//Imprime cadena espacio
  Serial.print("Payload -> ");//Imprime cadena
  payload[length] = 0;//Coloca un cero al final del byte array para convertirlo en cadena
  Serial.println((char *)payload);//Imprime puntero payload, que apunta a una cadena

  String miTopic = String(topic);//Crea objeto de la clase String con el contenido de topic
  String miPayload = String((char *)payload);//Crea objeto de la clase String con el contenido de payload

  /*
     Permite identificar mediante comparacion si se trata de algun topico subscrito.
  */
//   if (miTopic.equals(TOPICO_SUB_LED1)) {

//     if (miPayload.equals("1")) {
//       digitalWrite(PIN_LED1, HIGH);//Activa la salida del led1
//     } else {
//       digitalWrite(PIN_LED1, LOW);//Desactiva la salida del led1
//     }
}

void loop_ethernet(){
    auto link = Ethernet.linkStatus();
    Serial.print("Link status: ");
    switch (link)
    {
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

    if (millis() - previousMillis > INTERVAL)
    {
        sendData();
        previousMillis = millis();
    }
    client.loop();
}