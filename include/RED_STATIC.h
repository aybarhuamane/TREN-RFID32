
#include <SPI.h>
#include <UIPEthernet.h>
#include <UIPClient.h>
#include "PubSubClient.h"

UIPServer server = UIPServer(1883);
 
  uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};
//  IPAddress myIP(10,10,0,43);
//  IPAddress myDNS(10,10,0,1);
//const char *mqtt_server = "10.10.0.41";


  IPAddress myIP(172,19,38,204);
  IPAddress myDNS(172,19,38,1);
const char *mqtt_server = "172.19.34.200";


// MQTT
EthernetClient espClient;
PubSubClient client(espClient);
//PubSubClient mqttClient;
//#define SERVER "iotx.cloux.site"
#define PORT 1883

const char *mqtt_user = "python"; //ssid de la red
const char *mqtt_pass = "python$+"; //contraseña de la red
String clientId = "device12_" + String(random(0xffff),HEX);
#define ESTACION "vsalvador"
 // MQTT TOPIC

#define TOPICO_RAIZ "device/" "device12" "/estacion/" ESTACION "/data/"
#define TOPICO_PUB_DATA1 TOPICO_RAIZ "buscar" 
#define TOPICO_SUB_DATA1 TOPICO_RAIZ "encontrado"

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
    UIPEthernet.init(33); // ESP32 with Adafruit Featherwing Ethernet CS: 15

    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    
    Serial.println("Initialize Ethernet with Red:");
    //Ethernet.begin(mac, 1000UL,1000UL);
          UIPEthernet.begin(mac,myIP,myDNS);

          Serial.print("MY IP address:");
          Serial.println(UIPEthernet.localIP());
          Serial.println(UIPEthernet.gatewayIP());


  //if (UIPEthernet.begin(mac) == 0)
  //  {
        if (UIPEthernet.linkStatus() == LinkOFF)
        {
          Serial.println("Ethernet cable is not connected."); 
        }
        UIPEthernet.begin(mac,myIP,myDNS); 
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
           

        
    
}


void reconnect() {

  while (!client.connected()) {

    Serial.println("Intentando conexion MQTT");//Imprime cadena

    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass)) {
      //if (client.connect(clientId.c_str())){
      Serial.println("Conexion a MQTT exitosa!!");//Imprime cadena
     // print_lcdc("SERVER CONNECTED !");
      // INDICA CONEXION MQTT EXITOSA
      digitalWrite(ACT_MONGO,LOW);  //RELAY ABIERTO QUE NINGUN VALIDADOR LEA
      
        digitalWrite(REFID,HIGH);  // REVIVIMOS RFID
      client.subscribe(TOPICO_SUB_DATA1);   

    } else {
      Serial.print("Fallo la conexion ");//Imprime cadena
      Serial.println(client.state());//Imprime error de la conexion
      Serial.print(" Se intentara denuevo en 5 segundos");//Imprime cadena
      digitalWrite(ACT_MONGO,HIGH);  // RELAY CERRADO QUE EL OTRO VALIDADOR LEA
       digitalWrite(REFID,LOW);  // APAGAMOS EL RFID
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