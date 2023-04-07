// CORRECCION 14/09 00:30
//#include "LCD_20X4.h"
// correct 22_02_2023 Completo
bool stanby = false;
#include "DEFINIR.h"
#include <Separador.h>
#include "PIN.h"
#include<INDICADOR.h> // SE USA EN RED 
//#include "RED2.h"  //DHCP
//#include "REDW.h"  //WIFI
//#include "REC_RFID.h"
#include "RED_STATIC.h"
#include "RFID.h"
#include "MONGO.h"
#include <esp_task_wdt.h> //22/03
unsigned long t =0;
// bool printWebData = true; // set to false for better speed measurement

//#define IND2_MOONGO 22 

void setup()
{

    Serial.begin(115200);
    PINES();
   // bocina(4);
   // main_ethernet();

 //SI SE CONECTA A LA RED CORRECTAMENTE  TITILEA 3 VECES
    
      UIPEthernet.init(33);
      UIPEthernet.begin(mac,myIP,myDNS, gw, sn);
     // UIPEthernet.begin(mac,myIP,myDNS);
  server.begin();

  if (UIPEthernet.linkStatus() == LinkON)
  {
    Serial.println("conexion correcta");
  }
  else if (Ethernet.linkStatus() == LinkOFF)
     {
         Serial.println("Ethernet cable is not connected."); 
     }
    client.setServer(mqtt_server,PORT);
    server.begin();

   // antena_off(); // 25/02
    // if(suena==true)
    // {
    //     //bocina(3);
    //     Serial.println("CONECTADO");
    //   //  init_lcd("Red Connected!",3); 
    // }
    // else{
    //     //init_lcd("Fallo de conexion",3);
    //      Serial.println("NO CONECTADO");
    //   //  bocina(1);
    // }


    //RFID

        MRFID.begin(CLK_PIN_H, MISO_PIN_H, MOSI_PIN_H, SS_PIN_H); // //CLK,MISO,MOIS,SS.
        MRFID.begin(SS_PIN_H, OUTPUT);
        mfrc522.PCD_Init(); // Init MFRC522
       // antena_off();
        delay(4);           // Optional delay. Some board do need more time after init to be ready, see Readme
        mfrc522.PCD_DumpVersionToSerial(); // Show details of PCD - MFRC522 Card Reader details
        Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));   
        
        byte version = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
        if ((version == 0x00) || (version == 0xFF))
        {
            Serial.println(F("WARNING: PEPE Communication failure, is the MFRC522 properly connected?"));
             digitalWrite(rfid_led,LOW);
        }
        else{
          digitalWrite(rfid_led,HIGH);
        }
    // RED CONFIG
   
    //client.setClient(espClient);
    //client.setServer(mqtt_server,PORT);
    
  //Habilita o watchdog configurando o timeout para 4 segundos /22/03/2023
    // esp_task_wdt_init(60, true);
    // esp_task_wdt_add(NULL);
      //Habilita o watchdog configurando o timeout para 4 segundos
    esp_task_wdt_init(15, true);
    esp_task_wdt_add(NULL);
    client.setCallback(callback_mongo);
    Serial.println(F("MQTT client configured"));
    // previousMillis = millis();
    // beginMicros = micros();
}

void loop()
{

 if (client.connected() == false)
    {
        reconnect();

    }
    
         client.loop();
         loop_rfid();
         relay_NC(); //mongo.h

         ALERTA_ROJA();

  //Reseta o temporizador do watchdog
  esp_task_wdt_reset();  //22/03/2023

    // if (client.connected() == false)
    // {
    //     reconnect(); // Invoca la funcion "reconnect"
    // }
    // client.loop();
    // loop_rfid();



    //**************************** produce el error
    // if(client.state()== 0){
    // loop_rfid();
    // relay_NC(); //mongo.h

    // ALERTA_ROJA();
    // }

    //*************************
    
    //Serial.println(digitalRead(ACT_MONGO));
}

    