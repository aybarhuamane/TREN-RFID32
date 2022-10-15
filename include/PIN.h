#include "Arduino.h"
#include "SPI.h"
// ETHERNET
//#define CS_E 33
#define CS_E 33
// LED 
#define ACT_MONGO 22 //RELAY
#define IND1_MOONGO 21 //AZUL
#define ALERTA 16
#define REFID 17
// BUZ
#define BUZZER 4
//RFID
#define _CONFIG1 
#if defined _CONFIG1 
        //RFID : SPIClass MRFID(HSPI);  // DENTRO DE LA LIBRERIA MFRC522.cpp
        extern SPIClass MRFID;
        // #define RST_PIN_H 27  
        // #define SS_PIN_H 2
        // #define CLK_PIN_H 14
        // #define MOSI_PIN_H 13
        // #define MISO_PIN_H 12     

        #define RST_PIN_H 32  
        #define SS_PIN_H 2
        #define CLK_PIN_H 27  
        #define MOSI_PIN_H 26
        #define MISO_PIN_H 25     
#endif


void 
PINES()
{
    pinMode(BUZZER,OUTPUT);
    pinMode(IND1_MOONGO,OUTPUT);
    pinMode(ACT_MONGO,OUTPUT);
    pinMode(16,OUTPUT); //SALIDA PIC
    pinMode(ALERTA,OUTPUT); // SALIDA PIC
    pinMode(REFID,OUTPUT); // SALIDA PIC
    // pinMode(IND2_MOONGO,OUTPUT);
    digitalWrite(IND1_MOONGO,LOW); //INICIA EN OFF
    digitalWrite(ALERTA,LOW); //SALIDA PIC
    digitalWrite(REFID,HIGH); // ACTIVAMOS  RFID1

     
    // digitalWrite(17,LOW); // SALIDA PIC
   // digitalWrite(ACT_MONGO,LOW); // relay  antes  14/10/2022


    // digitalWrite(ALERTA,HIGH);
    // delay(2000);
    // digitalWrite(ALERTA,LOW);
    //  delay(2000);

    //      digitalWrite(ALERTA,HIGH);
    // delay(2000);
    // digitalWrite(ALERTA,LOW);
    //  delay(2000);
// pinMode(5,OUTPUT);
//    digitalWrite(5,HIGH); 

    //init_lcd("Iniciando...",1);
}