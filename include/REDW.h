#include <WiFi.h>
#include <PubSubClient.h>

//const char* ssid = "LINEA1_PRIVADO";
//const char* password = "M3tr0deL1m@2#17";
//const char* mqtt_server = "192.168.173.143";
//const char* mqtt_server = "172.19.34.17";

//  const char* ssid = "LINEA1_PRIVADO";
//  const char* password = "M3tr0deL1m@2#17";
// const char* mqtt_server = "172.19.34.200";
// const char *mqtt_user = "device-rfid"; //ssid de la red
// const char *mqtt_pass = "device$+"; //contraseña de la red

const char* ssid = "MOVISTAR_2019";
const char* password = "movistar123$+";
const char *mqtt_user = "python"; //ssid de la red
const char *mqtt_pass = "python$+"; //contraseña de la red
const char* mqtt_server = "192.168.1.81";

// const char* ssid = "Wifi_Comedor";
// const char* password = "movistar123";
//const char* mqtt_server = "192.168.1.81";
//const char *mqtt_server = "192.168.16.101";
//const char* mqtt_server = "localhost";
//const char* mqtt_server = "192.168.173.143";



//PubSubClient mqttClient;
//#define SERVER "iotx.cloux.site"
#define PORT 1883

//String client=  "client12" +  String(random(0xffff));
#define clientId  "device-rfid"
#define ESTACION "CULTURA"
 // MQTT TOPIC
const char *client_randon = clientId + (random(0xffff),HEX);
#define TOPICO_RAIZ "device/" clientId "/estacion/" ESTACION "/data/"
#define TOPICO_PUB_DATA1 TOPICO_RAIZ "buscar" 
#define TOPICO_SUB_DATA1 TOPICO_RAIZ "encontrado"


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
WiFiClient espClient;
PubSubClient client(espClient);


void reconnect() {

 while (!client.connected()) {

    Serial.println("Intentando conexion MQTT");//Imprime cadena
    //clientId = clientId + String(random(0xffff), HEX);//Genera una cadena con valor random
    if (client.connect(client_randon, mqtt_user, mqtt_pass)) {
      //if (client.connect(clientId.c_str())){
      Serial.println("Conexion a MQTT exitosa!!");//Imprime cadena
     // print_lcdc("SERVER CONNECTED !");
      // INDICA CONEXION MQTT EXITOSA
      //parpadeo(false); 
     client.subscribe(TOPICO_SUB_DATA1);//Suscripcion a topico
      // client.subscribe(TOPICO_SUB_DATA2);
      // client.subscribe(TOPICO_SUB_DATA3);
      // client.subscribe(TOPICO_SUB_DATA4);
     // client.subscribe(TOPICO_PUB_DATA3); //activar si usa NA RELAY
      //client.publish(TOPICO_PUB_DATA1, "BIEVENIDO");

    } else {
      Serial.print("Fallo la conexion ");//Imprime cadena
      Serial.println(client.state());//Imprime error de la conexion
      Serial.print(" Se intentara denuevo en 5 segundos");//Imprime cadena

      delay(2000);//Espera 2 segundos para seguir intentando conectarse 
      incremento+=1;   //-> se movio al indicador.h

     // print_lcd("Reconnecting..");
      //parpadeo(true); // parpadea el indicador
     
     if (incremento > 5){
      Serial.println("\nReiniciando por fallo MQTT SERVER...");
        ESP.restart();
        
     }
    }
  }
}

void main_ethernet() {

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid,password);

  while (WiFi.status() != WL_CONNECTED) {
    
    delay(500);
    Serial.print(".");

  }
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}