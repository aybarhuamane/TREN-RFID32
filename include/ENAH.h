#include <Arduino.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define RST_PIN 15
#define SS_PIN 21
// WIFI
const char *ssid = "Wifi_Comedor";
const char *password = "movistar123";
WiFiClient espClient;
PubSubClient client(espClient);

// MQTT
const char *mqtt_server = "proyect.cloux.site";
const char *mqtt_user = "adminx"; // ssid de la red
const char *mqtt_pass = "adminx"; // contraseña de la red
#define port 1883
#define TOPICO_RAIZ "data/"
#define TOPICO_DATA1 TOPICO_RAIZ "asa"
#define TOPICO_DATA2 TOPICO_RAIZ "asa"

// OTROS
String hostname = "lector-wifi";
#define TOPICO_DATA "data/asa"
int incremento = 0;
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

int x = 0;
String dni = "";

void setup_wifi(const char *ssid, const char *password)
{

    Serial.println();               // Imprime nueva linea
    Serial.print("Conectando a: "); // Imprime cadena
    Serial.println(ssid);           // Imprime cadena con el contenido de ssid

    WiFi.begin(ssid, password); // Configura el WIFI del modulo
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);        // Espera de 500mseg
        Serial.print("."); // Imprime cadena
    }

    Serial.println("");                           // Imprime cadena
    Serial.println("Conectando a la red Wifi! "); // Imprime cadena
    Serial.print("Direccion IP: ");               // Imprime cadena
    Serial.println(WiFi.localIP());               // Imprime la ip asignada por el router local
    
}


void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("MENSAJE ENVIADO [");
    Serial.print(topic);
    Serial.print("] ");
}

void reconnect(String nameID)
{
    while (!client.connected())
    {
        Serial.print("Attempting connecting server..");
        // Create a random client ID
        String clientId = nameID;
        clientId += String(random(0xffff), HEX);
        // Attempt to connect
        if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass))
        {
            Serial.println("connected");
            client.subscribe(TOPICO_DATA1);
            // client.publish(TOPICO_DATA ,"0 0 0 0 4B");
            Serial.println("Enviado... ");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            ESP.restart();
        }
    }
}

void setup()
{
    // MQTT WIFI();
     //setup_wifi();
    client.setServer(mqtt_server, port);
    client.setCallback(callback);
}

void loop_mqtt(String nameID)
{
        if (!client.connected())
    {
        reconnect(nameID);
    }
    client.loop();
}

