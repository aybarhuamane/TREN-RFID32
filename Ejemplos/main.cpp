
#include "EAH.h"
#include <MFRC522.h>
//  LCD https://www.youtube.com/watch?v=Frn5ZaxUYEI
#define _CONFIG1 //RFID
//#define _CONFIG2 //LCD 
//#define _CONFIG3 //RFID PIN LCD

//#ifndef _CONFIG1
//        #define _CONFIG2
//#endif


// WIFI
const char *ssid = "Wifi_Comedor";
const char *password = "movistar123";


// MQTT
const char *mqtt_server = "proyect.cloux.site";
const char *mqtt_user = "adminx"; // ssid de la red
const char *mqtt_pass = "adminx"; // contraseña de la red
String clientId = "device_rfid";

#define port 1883
#define TOPICO_RAIZ "data/"
#define TOPICO_DATA1 TOPICO_RAIZ "asa"
#define TOPICO_DATA2 TOPICO_RAIZ "asa"


#if defined (_CONFIG1) && defined (_CONFIG2)
        //RFID
        #define RST_PIN_H 27  
        #define SS_PIN_H 15
        #define CLK_PIN_H 14
        #define MOSI_PIN_H 13
        #define MISO_PIN_H 12
        // LCD
        #define SS_PIN 5
        #define CLK_PIN 18
        #define MOSI_PIN 23
        #define MISO_PIN 19

#elif defined _CONFIG1 
        //RFID : SPIClass MRFID(HSPI);  // DENTRO DE LA LIBRERIA MFRC522.cpp
        extern SPIClass MRFID;
        #define RST_PIN_H 27  
        #define SS_PIN_H 15
        #define CLK_PIN_H 14
        #define MOSI_PIN_H 13
        #define MISO_PIN_H 12
     
#elif defined _CONFIG2 
        // LCD
        //SPIClass SPI(VSPI);  //definir dentro de la libreria y cambiar la variable SPI

        #define SS_PIN 5
        #define CLK_PIN 18
        #define MOSI_PIN 23
        #define MISO_PIN 19

#elif defined _CONFIG3 
        //RFID2
        // SPIClass SPI2(VSPI);
        #define RST_PIN_H 27

        #define SS_PIN_H 5
        #define CLK_PIN_H 18
        #define MOSI_PIN_H 23
        #define MISO_PIN_H 19
#endif

unsigned long tiempo = 0;
#define periodo 3000UL
EAH iot;
MFRC522 mfrc522(SS_PIN_H, RST_PIN_H); // Create MFRC522 instance

void setup()
{
        Serial.begin(115200);
        while (!Serial)
                ;
        // SPI.begin();
        MRFID.begin(CLK_PIN_H, MISO_PIN_H, MOSI_PIN_H, SS_PIN_H); // //CLK,MISO,MOIS,SS.
        MRFID.begin(SS_PIN_H, OUTPUT);
        mfrc522.PCD_Init(); // Init MFRC522
        delay(4);           // Optional delay. Some board do need more time after init to be ready, see Readme

        mfrc522.PCD_DumpVersionToSerial(); // Show details of PCD - MFRC522 Card Reader details
        Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

        //MQTT
        iot.setup_wifi(mqtt_user,mqtt_pass);  //WIFI : USER , PASS
        //setServer(mqtt_server, port);
        //client.setCallback(callback);

}
byte ActualUID[4]; // almacenará el código del Tag leído

// Función para comparar dos vectores
boolean compareArray(byte array1[], byte array2[])
{
        if (array1[0] != array2[0])
                return (false);
        if (array1[1] != array2[1])
                return (false);
        if (array1[2] != array2[2])
                return (false);
        if (array1[3] != array2[3])
                return (false);
        return (true);
}

void loop()
{

 iot.loop_iot(clientId,mqtt_user,mqtt_pass); // IDNAME , USER, PASSW


        if (mfrc522.PICC_IsNewCardPresent())
        {
                if (mfrc522.PICC_ReadCardSerial())
                {

                        if (millis() - tiempo > periodo)
                        {

                                Serial.println(F("\nCard UID:"));

                                for (byte i = 0; i < mfrc522.uid.size; i++)
                                {
                                        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                                        Serial.print(mfrc522.uid.uidByte[i], HEX);
                                        ActualUID[i] = mfrc522.uid.uidByte[i];
                                }
                                tiempo = millis();
                        }
                        // if( compareArray(ActualUID, ) )
                        // {

                        // }
                }
        }
}
