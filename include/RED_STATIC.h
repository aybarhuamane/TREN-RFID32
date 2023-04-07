// 14/02/2023
#include <SPI.h>
#include <UIPEthernet.h>
#include <UIPServer.h>
#include <UIPClient.h>
#include "PubSubClient.h"


UIPServer server = UIPServer(1883);


 //******************* ASUS SIMULADOR DOCKER ************ TORNIQUETE 5


//   IPAddress myIP(192,168,1,66);
//   IPAddress myDNS(192,168,1,1);
//   IPAddress gw(192,168,1,1);
//   IPAddress sn(255,255,255,0);
//  const char *mqtt_server = "192.168.1.62";




 //*******************DEVICE 1 ************ TORNIQUETE 5

//   uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};
//  IPAddress myIP(10,10,19,50);
//  IPAddress myDNS(10,10,0,1);
//  IPAddress gw(10,10,0,1);
//  IPAddress sn(255,255,0,0);
// const char *mqtt_server = "10.10.0.41";


//  //*******************DEVICE 2*********** TORNIQUETE 4

 uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x02};
 IPAddress myIP(10,10,19,20);  //10.52  libre
 IPAddress myDNS(10,10,19,1);
 IPAddress gw(10,10,19,1);
 IPAddress sn(255,255,0,0);
const char *mqtt_server = "10.10.0.41";

#define clientId  "01002"
#define ESTACION "19"
String client_randon = "01002_" + (String)(random(0xffff),HEX);

//*************LABORATORIO
// IPAddress myIP(172,19,40,104);
// IPAddress myDNS(172,19,40,1);
// const char *mqtt_server = "172.19.34.200";

//************* SIO ADMINISTRATIVA

// #define clientId  "SIO"
// #define ESTACION "SIO-"
// String client_randon = "SIO-" + (String)(random(0xffff),HEX);
// IPAddress myIP(172,19,34,80);
// IPAddress myDNS(172,19,34,1);
// IPAddress gw(172,19,34,1);
// IPAddress sn(255,255,255,0);
// const char *mqtt_server = "172.19.34.200";

//****** OPERATIVA
//   IPAddress myIP(10,10,0,46);
//   IPAddress myDNS(10,10,0,1);
//   IPAddress gw(10,10,0,1);
// IPAddress sn(255,255,255,0);
// const char *mqtt_server = "10.10.0.45";

// MQTT
EthernetClient espClient;
PubSubClient client(espClient);

//PubSubClient mqttClient;
//#define SERVER "iotx.cloux.site"
#define PORT 1883

 // MQTT TOPIC
const char *mqtt_user = "python"; //ssid de la red
const char *mqtt_pass = "python$+"; //contraseña de la red
//************ DEVICE 1
// String clientId = "device_1_" + String(random(0xffff),HEX);
// #define ESTACION "cajadeagua"
// #define TOPICO_RAIZ "device/" "device_1_" "/station/" ESTACION "/data/"

// ************ DEVICE 2
// String clientId = "device_2" + (String)(random(0xffff),HEX);
// #define ESTACION "cajadeagua"
// #define TOPICO_RAIZ "device/" "device_2" "/station/" ESTACION "/data/"

// #define TOPICO_PUB_DATA1 TOPICO_RAIZ "buscar"
// #define TOPICO_SUB_DATA1 TOPICO_RAIZ "encontrado"

#define TOPICO_RAIZ "device/" clientId "/station/" ESTACION "/data/"
#define TOPICO_PUB_DATA1 TOPICO_RAIZ "buscar" 
#define TOPICO_SUB_DATA1 TOPICO_RAIZ "encontrado"


//************DEVICE 2
// String clientId = "device_2_" + String(random(0xffff),HEX);
// #define ESTACION "cajadeagua"
// #define TOPICO_RAIZ "device/" "device_2_" "/station/" ESTACION "/data/"

// #define TOPICO_PUB_DATA1 TOPICO_RAIZ "buscar"
// #define TOPICO_SUB_DATA1 TOPICO_RAIZ "encontrado"

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
bool main_ethernet()
{
    UIPEthernet.init(33); // ESP32 with Adafruit Featherwing Ethernet CS: 15

    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    Serial.println("Initialize Ethernet with Red:");
    //Ethernet.begin(mac, 1000UL,1000UL);
         // UIPEthernet.begin(mac,myIP,myDNS);
          UIPEthernet.begin(mac,myIP,myDNS, gw, sn);
          Serial.print("MY IP address:");
          Serial.println(UIPEthernet.localIP());
          Serial.println(UIPEthernet.gatewayIP());


  //if (UIPEthernet.begin(mac) == 0)
  //  {
        if (UIPEthernet.linkStatus() == LinkOFF)
        {
          Serial.println("Ethernet cable is not connected.");
        }
       // UIPEthernet.begin(mac,myIP,myDNS);

 //   }

    if (UIPEthernet.linkStatus() == LinkON)
      {
        Serial.println("conexion correcta");
      }

    // if (UIPEthernet.begin(mac) == 0)
    // {
    //     Serial.println("Failed to configure Ethernet using Red");
    //         Serial.println("Reiniciando ...");
    //         delay(1500);
    //         ESP.restart();
    //     // Check for Ethernet hardware present
    //     if (UIPEthernet.hardwareStatus() == EthernetNoHardware)
    //     {

    //         Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");

    //         while (true)
    //         {
    //             delay(1); // do nothing, no point running without Ethernet hardware
    //         }
    //     }
    //     if (UIPEthernet.linkStatus() == LinkOFF)
    //     {
    //         Serial.println("Ethernet cable is not connected.");

    //     }



    return true;
}

bool main_ethernet2()
{
  UIPEthernet.init(33);
  UIPEthernet.begin(mac,myIP,myDNS);

  server.begin();

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
void reconnect() {

  while (!client.connected()) {

    Serial.println("Intentando conexion MQTT");//Imprime cadena
    digitalWrite(intermitente,HIGH); // PINTA EL X HASTA QUE SE ESTABLEZCA LA CONEXION CORRECTA
    // main_ethernet();
    //  main_ethernet2(); borrado
    if (client.connect(client_randon.c_str(), mqtt_user, mqtt_pass)) {
      //if (client.connect(clientId.c_str())){
      Serial.println("Conexion a MQTT exitosa!!");//Imprime cadena
     // print_lcdc("SERVER CONNECTED !");

     //digitalWrite(ACT_MONGO, LOW); //ABRE EL CIRCUITO
     digitalWrite(ACT_MONGO, HIGH); //ABRE EL CIRCUITO
     digitalWrite(intermitente,LOW); // DESPINTA CUANDO YA SE CONECTO
     //digitalWrite(ind_server,HIGH);
     antena_on();
     
      // INDICA CONEXION MQTT EXITOSA

      //digitalWrite(ACT_MONGO,LOW);  //RELAY ABIERTO QUE NINGUN VALIDADOR LEA
       stanby = true;
      // digitalWrite(REFID,HIGH);  // REVIVIMOS RFID
      client.subscribe(TOPICO_SUB_DATA1);
      client.subscribe(TOPICO_PUB_DATA1); 
      client.publish(TOPICO_PUB_DATA1,"12345678"); 
    } else {
      Serial.print("Fallo la conexion ");//Imprime cadena
      Serial.println(client.state());//Imprime error de la conexion
      Serial.print(" Se intentara denuevo en 5 segundos");//Imprime cadena
   //   digitalWrite(ACT_MONGO,HIGH);  // RELAY CERRADO QUE EL OTRO VALIDADOR LEA
      antena_off();
      //digitalWrite(ACT_MONGO, HIGH); // CIERRA RFID2 SE MANTIENE ESCUCHANDO
      digitalWrite(ACT_MONGO, LOW); // CIERRA RFID2 SE MANTIENE ESCUCHANDO
      //digitalWrite(ind_server,LOW);

      // digitalWrite(REFID,LOW);  // APAGAMOS EL RFID

      //delay(2000);//Espera 2 segundos para seguir intentando conectarse
      incremento+=1;   //-> se movio al indicador.h

     // print_lcd("Reconnecting..");

      delay(1000);
     if (incremento > 5){
      Serial.println("\nReiniciando por fallo MQTT SERVER...");
      ESP.restart();

     }
    }
  }
}

// void loop_ethernet(){
//     auto link = Ethernet.linkStatus();
//     Serial.print("Link status: ");
//     switch (link)
//     {
//     case Unknown:
//         Serial.println("Unknown");
//         break;
//     case LinkON:
//         Serial.println("ON");
//         break;
//     case LinkOFF:
//         Serial.println("OFF");
//         break;
//     }
//     delay(1000);

//     if (millis() - previousMillis > INTERVAL)
//     {
//         sendData();
//         previousMillis = millis();
//     }
//     client.loop();
// }