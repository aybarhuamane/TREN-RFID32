#include <Arduino.h>
#include "EAH.h"
WiFiClient espClient;
PubSubClient client(espClient);


void EAH::setup_wifi(const char *ssid, const char *password)
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

void EAH::callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("MENSAJE ENVIADO [");
    Serial.print(topic);
    Serial.print("] ");
}

void EAH::loop_iot(String clientId ,const char *mqtt_users,const char *mqtt_passs)
{

    if (!client.connected())
    {

        while (!client.connected())
        {
            Serial.print("Attempting connecting server..");
            // Create a random client ID
            clientId += String(random(0xffff), HEX);
            // Attempt to connect
            if (client.connect(clientId.c_str(), mqtt_users, mqtt_passs))
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
    client.loop();
}

// void EAH::reconnect(String nameID)
// {
//     while (!client.connected())
//     {
//         Serial.print("Attempting connecting server..");
//         // Create a random client ID
//         String clientId = nameID;
//         clientId += String(random(0xffff), HEX);
//         // Attempt to connect
//         if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass))
//         {
//             Serial.println("connected");
//             client.subscribe(TOPICO_DATA1);
//             // client.publish(TOPICO_DATA ,"0 0 0 0 4B");
//             Serial.println("Enviado... ");
//         }
//         else
//         {
//             Serial.print("failed, rc=");
//             Serial.print(client.state());
//             Serial.println(" try again in 5 seconds");
//             ESP.restart();
//         }
//     }
// }

// void EAH::loop_mqtt(String nameID)
// {
//         if (!client.connected())
//     {
//         reconnect(nameID);
//     }
//     client.loop();
// }
