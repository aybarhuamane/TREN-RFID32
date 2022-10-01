
#include<INDICADOR.h> // SE USA EN RED 
#include "RED.h"
#include "RFID.h"
#include "MONGO.h"


unsigned long t =0;
// bool printWebData = true; // set to false for better speed measurement

//#define IND2_MOONGO 22 

void setup()
{

    Serial.begin(115200);
    pinMode(BUZZER,OUTPUT);
    pinMode(IND1_MOONGO,OUTPUT);
    pinMode(16,OUTPUT);
    pinMode(17,OUTPUT);
   // pinMode(IND2_MOONGO,OUTPUT);
    digitalWrite(IND1_MOONGO,LOW); //INICIA EN OFF
    digitalWrite(16,LOW);
    digitalWrite(17,LOW);

    Ethernet.init(33); // ESP32 with Adafruit Featherwing Ethernet CS: 15
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    Serial.println("Initialize Ethernet with DHCP:");
    if (Ethernet.begin(mac) == 0)
    {
        Serial.println("Failed to configure Ethernet using DHCP");
        // Check for Ethernet hardware present
        if (Ethernet.hardwareStatus() == EthernetNoHardware)
        {
            Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
            Serial.println("Reiniciando ...");
            delay(1500);
            ESP.restart();
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
        Ethernet.begin(mac, ip, myDns);
        
    }

 //SI SE CONECTA A LA RED CORRECTAMENTE  TITILEA 3 VECES
    suena==true ? bocina(3) : bocina(1);
    

    //RFID

        MRFID.begin(CLK_PIN_H, MISO_PIN_H, MOSI_PIN_H, SS_PIN_H); // //CLK,MISO,MOIS,SS.
        MRFID.begin(SS_PIN_H, OUTPUT);
        mfrc522.PCD_Init(); // Init MFRC522
        delay(4);           // Optional delay. Some board do need more time after init to be ready, see Readme
        mfrc522.PCD_DumpVersionToSerial(); // Show details of PCD - MFRC522 Card Reader details
        Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));   

    // RED CONFIG
    client.setClient(espClient);
    client.setServer(mqtt_server,PORT);
    client.setCallback(callback_mongo);
    Serial.println(F("MQTT client configured"));
    previousMillis = millis();
    beginMicros = micros();
}

void loop()
{
    if (client.connected() == false)
    {
        reconnect(); // Invoca la funcion "reconnect"
    }
    client.loop();

    loop_rfid();


}
