
#include <SPI.h>
#include <EthernetENC.h>
#include "PubSubClient.h"

//#define PLANTA3 // LABORAT
//#define PLANTA2
uint8_t mac[] = {0x00,0x01,0x02,0x03,0x04,0x05};
//const byte mac[] PROGMEM = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//byte mac[] =  {0x8B, 0xAA, 0xB5, 0xA2, 0x14, 0xB0};
//#define MYIPADDR 172,19,34,45
//#define MYIPMASK 255,255,255,0
//#define MYDNS 172,19,34,1
//#define MYGW 172,19,34,1
//
// #define MYIPADDR 192,168,1,42
// #define MYIPMASK 255,255,255,0
// #define MYDNS 192,168,1,1
// #define MYGW 192,168,1,1

//#define MYIPADDR 10,10,0,44
//#define MYIPMASK 255,255,255,0
//#define MYDNS 10,10,0,1
//#define MYGW 10,10,0,1


IPAddress myIP(10,10,0,43);
IPAddress myDNS(10,10,0,1);
const char *mqtt_server = "10.10.0.41";


#if defined PLANTA
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// IPAddress ip(10, 10, 0, 51);
// IPAddress myDns(10,10,0,1); 
//IPAddress ip(172, 19, 34,250); //172.19.34.17 - 250  //ESTA IP SERA ASIGNADO AL MODULO ETHERTNET 
//IPAddress myDns(172,24,34,1); //  172.19.34.1

//IPAddress myDns(172,19,20,31);
//  172.19.34.1 puerta de enlace 

// 
// DNS :172.24.20.198
// 172.24.20.31

//IPAddress myDns(192, 168, 1, 1); //

// MQTT
const char *mqtt_server = "172.19.34.17";  // SERA LA IP DONDE ESTA ALOJADO EL SERVER LOCAL SI ES PC, SERA IP DE LA PC
#elif defined PLANTA2
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(10,10,0,51); 
IPAddress myDns(10,10,0,1);
const char *mqtt_server = "10.10.0.40";
#elif defined PLANTA3
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(172,19,40,57);  // 169.254.93.46
IPAddress myDns(172,19,40,1); // 255.255.0.0

const char *mqtt_server = "172.19.40.58";
#elif defined CASA2 
byte mac[] = {0x30, 0x2B, 0x2D, 0x35, 0x51, 0xA2};
IPAddress ip(192,168,1,34); //ip que se  asignara al modulo
IPAddress myDns(192,168,1,1); 
const char *mqtt_server = "proyect.cloux.site";
#elif defined CASA 
// ETHERNET
byte mac[] = {0x30, 0x2B, 0x2D, 0x35, 0x51, 0xA2};
//byte mac[] = {0xFF, 0xFF, 0xFF , 0xFF, 0x00};    
// byte mac[] = {0x01,0x02,0x03,0x04, 0x05} ;      
//byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 
//char server[] = "www.google.com"; // name address for Google (using DNS)
IPAddress ip(10, 10, 0, 51); //ip que se  asignara al modulo
IPAddress myDns(10,10,0,1); 
// IPAddress ip(192, 168, 1, 17);  //
// IPAddress myDns(192,168,1,1);
// MQTT
// const char *mqtt_server = "192.168.1.79";
const char *mqtt_server = "10.10.0.100";



#endif
// MQTT
EthernetClient espClient;
PubSubClient client(espClient);
//PubSubClient mqttClient;
//#define SERVER "iotx.cloux.site"
#define PORT 1883

const char *mqtt_user = "python"; //ssid de la red
const char *mqtt_pass = "python$+"; //contraseña de la red
#define clientId  "device-rfid"
#define ESTACION "CULTURA"
 // MQTT TOPIC
const char *client_randon = clientId + (random(0xffff),HEX);
#define TOPICO_RAIZ "device/" clientId "/estacion/" ESTACION "/data/"
#define TOPICO_PUB_DATA1 TOPICO_RAIZ "buscar" 
#define TOPICO_SUB_DATA1 TOPICO_RAIZ "encontrado"

 // MQTT TOPIC

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
void main_ethernet()
{
    Ethernet.init(CS_E); // ESP32 with Adafruit Featherwing Ethernet CS: 15

    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    
    Serial.println("Initialize Ethernet with Red:");
    //Ethernet.begin(mac, 1000UL,1000UL);

      Ethernet.begin(mac, myIP);

    if (Ethernet.begin(mac) == 0)
    {
        Serial.println("Failed to configure Ethernet using Red");
            Serial.println("Reiniciando ...");
            delay(1500);
            ESP.restart();
        // Check for Ethernet hardware present
        if (Ethernet.hardwareStatus() == EthernetNoHardware)
        {
            suena = false;
            Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");

            while (true)
            {
                delay(1); // do nothing, no point running without Ethernet hardware
            }
        }
        if (Ethernet.linkStatus() == LinkOFF)
        {
            Serial.println("Ethernet cable is not connected.");
            suena = false;
        }
        // try to congifure using IP address instead of DHCP:
          // IPAddress ip(MYIPADDR);
          // IPAddress dns(MYDNS);
          // IPAddress gw(MYGW);
          // IPAddress sn(MYIPMASK);

          //      IPAddress ip(MYIPADDR);
          //      IPAddress dns(MYDNS);
          //      IPAddress gw(MYGW);
          //      IPAddress sn(MYIPMASK);

         //  Ethernet.begin(mac, ip, dns, gw, sn);
        //   Ethernet.begin(mac, ip);
          // Serial.println("STATIC OK!");
           

            Ethernet.begin(mac, myIP);
        // Ethernet.begin(mac, ip, dns);

          Serial.print("MY IP address:");
          Serial.println(Ethernet.localIP());
          Serial.println(Ethernet.gatewayIP());
        
    }
}


void reconnect() {

  while (!client.connected()) {

    Serial.println("Intentando conexion MQTT");//Imprime cadena

    if (client.connect(client_randon, mqtt_user, mqtt_pass)) {
      //if (client.connect(clientId.c_str())){
      Serial.println("Conexion a MQTT exitosa!!");//Imprime cadena
     // print_lcdc("SERVER CONNECTED !");
      // INDICA CONEXION MQTT EXITOSA
      parpadeo(false); 
      client.subscribe(TOPICO_SUB_DATA1);   

    } else {
      Serial.print("Fallo la conexion ");//Imprime cadena
      Serial.println(client.state());//Imprime error de la conexion
      Serial.print(" Se intentara denuevo en 5 segundos");//Imprime cadena

      //delay(2000);//Espera 2 segundos para seguir intentando conectarse 
      incremento+=1;   //-> se movio al indicador.h

     // print_lcd("Reconnecting..");
      parpadeo(true); // parpadea el indicador
      delay(2000);
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