
#include "MONGO.h"
#include "RED.h"
#include "RFID.h"

// bool printWebData = true; // set to false for better speed measurement

void setup()
{

    Serial.begin(115200);

    Ethernet.init(15); // ESP32 with Adafruit Featherwing Ethernet CS: 15
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
            while (true)
            {
                delay(1); // do nothing, no point running without Ethernet hardware
            }
        }
        if (Ethernet.linkStatus() == LinkOFF)
        {
            Serial.println("Ethernet cable is not connected.");
        }
        // try to congifure using IP address instead of DHCP:
        Ethernet.begin(mac, ip, myDns);
    }
    else
    {
        Serial.print("  DHCP assigned IP ");
        Serial.println(Ethernet.localIP());
    }

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
