#include <UIPEthernet.h>
#include <UIPServer.h>
#include <UIPClient.h>
#include "PubSubClient.h"
UIPServer server = UIPServer(1883);
 
  uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};
//   IPAddress myIP(10,10,0,46);
//   IPAddress myDNS(10,10,0,1);
// const char *mqtt_server = "10.10.0.45";


IPAddress myIP(172,19,34,28);
IPAddress myDNS(172,19,34,1);
IPAddress gw(172,19,34,1);
IPAddress sn(255,255,255,0);
const char *mqtt_server = "172.19.34.200";

// MQTT
EthernetClient espClient;
PubSubClient client(espClient);
//PubSubClient mqttClient;
//#define SERVER "iotx.cloux.site"
#define PORT 1883

const char *mqtt_user = "python"; //ssid de la red
const char *mqtt_pass = "python$+"; //contraseña de la red
#define clientId  "device-rfid"
#define ESTACION "vsalvador"
 // MQTT TOPIC
String client_randon = "device-rfid" + (String)(random(0xffff),HEX);
#define TOPICO_RAIZ "device/" clientId "/station/" ESTACION "/data/"
#define TOPICO_PUB_DATA1 TOPICO_RAIZ "buscar" 
#define TOPICO_SUB_DATA1 TOPICO_RAIZ "encontrado"


//MILLS
long previousMillis;
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
#define INTERVAL 3000 // 3 sec delay between publishing
int incremento =0;


void reconnect() {

  while (!client.connected()) {

    Serial.println("Intentando conexion MQTT");//Imprime cadena

    if (client.connect(client_randon.c_str() , mqtt_user, mqtt_pass)) {
      //if (client.connect(clientId.c_str())){
      Serial.println("Conexion a MQTT exitosa!!");//Imprime cadena
     // print_lcdc("SERVER CONNECTED !");
      // INDICA CONEXION MQTT EXITOSA
      Serial.println(TOPICO_PUB_DATA1);
      client.subscribe(TOPICO_PUB_DATA1); 
      client.publish(TOPICO_PUB_DATA1,"620547803"); 
        

    } else {
      Serial.print("Fallo la conexion ");//Imprime cadena
      Serial.println(client.state());//Imprime error de la conexion
      Serial.print(" Se intentara denuevo en 5 segundos");//Imprime cadena

      //delay(2000);//Espera 2 segundos para seguir intentando conectarse 
      incremento+=1;   //-> se movio al indicador.h

     // print_lcd("Reconnecting..");
  
      delay(2000);
     if (incremento > 5){
      Serial.println("\nReiniciando por fallo MQTT SERVER...");
        ESP.restart();
        
     }
    }
  }
}


void setup() {

   Serial.begin(115200);
 
  UIPEthernet.init(33);
  UIPEthernet.begin(mac,myIP,myDNS);

  server.begin();
  
//       while (!Serial)
//     {
//         ; // wait for serial port to connect. Needed for native USB port only
//     }

  
  if (UIPEthernet.linkStatus() == LinkON)
  {
    Serial.println("conexion correcta");
  }
  if (Ethernet.linkStatus() == LinkOFF)
 {
     Serial.println("Ethernet cable is not connected."); 
 }
client.setServer(mqtt_server,PORT);
server.begin();


}

void loop() {
  //   auto link = UIPEthernet.linkStatus();
  //   Serial.print("Link status: ");
  //   switch (link) {
  //   case Unknown:
  //     Serial.println("Unknown");
  //     break;
  //   case LinkON:
  //     Serial.println("ON");
  //     break;
  //   case LinkOFF:
  //     Serial.println("OFF");
  //     break;
  // }
  // delay(500);
    if (client.connected() == false)
    {
        reconnect(); // Invoca la funcion "reconnect"
    }
     client.loop();

     client.publish(TOPICO_PUB_DATA1,"620547803");
     delay(300); 
  // if (UIPClient client = server.available()) {

  //   Serial.println("HOla");
  //   if (client) {

      
  //     while (client.available()) {
  //       int c = client.read();
  //       client.write(c);
  //     }
  //   }
  // }
}