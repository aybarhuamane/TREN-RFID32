#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
//#include <INDICADOR.h>
        #define RST_PIN_H 32  
        #define SS_PIN_H 2
        #define CLK_PIN_H 27  
        #define MOSI_PIN_H 26
        #define MISO_PIN_H 25   
        extern SPIClass MRFID;
        MFRC522 mfrc522(SS_PIN_H, RST_PIN_H); // Create MFRC522 instance

#define relay 17
#define led_rfid 13
void setup()
{

    Serial.begin(115200);
    pinMode(led_rfid,OUTPUT);
    while (!Serial); 
 
    //RFID

        MRFID.begin(CLK_PIN_H, MISO_PIN_H, MOSI_PIN_H, SS_PIN_H); // //CLK,MISO,MOIS,SS.
        MRFID.begin(SS_PIN_H, OUTPUT);
        mfrc522.PCD_Init(); // Init MFRC522
        delay(4);           // Optional delay. Some board do need more time after init to be ready, see Readme
        mfrc522.PCD_DumpVersionToSerial(); // Show details of PCD - MFRC522 Card Reader details
        Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks...")); 
        // ENCIENDE LED INDICANDO QUE COMUNICA
        byte version = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
        if ((version == 0x00) || (version == 0xFF))
        {
            Serial.println(F("WARNING: PEPE Communication failure, is the MFRC522 properly connected?"));
             digitalWrite(led_rfid,LOW);
        }
        else{
          digitalWrite(led_rfid,HIGH);
        }

 pinMode(relay,OUTPUT);
 digitalWrite(relay,HIGH);
 delay(200);      
  digitalWrite(relay,LOW); 
}

void loop()
{


if ( mfrc522.PICC_IsNewCardPresent()) {
            if ( mfrc522.PICC_ReadCardSerial()) 
            {
                  Serial.println(F("Card UID:"));
                  for (byte i = 0; i < mfrc522.uid.size; i++) {
                          Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                          Serial.print(mfrc522.uid.uidByte[i], HEX);   

                  }
                //  bocina(1);
               //   delay(1000);
                 // mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
            }
            
    }


}
