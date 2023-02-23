
#include <MFRC522.h>
#include <PIN.h>

MFRC522 mfrc522(SS_PIN_H, RST_PIN_H); // Create MFRC522 instance

void reconect_rfid()
{
        mfrc522.PCD_Init(); // Init MFRC522
        delay(4);           // Optional delay. Some board do need more time after init to be ready, see Readme
        mfrc522.PCD_DumpVersionToSerial(); // Show details of PCD - MFRC522 Card Reader details
        Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));   
}

void antena_off()
{
        mfrc522.PCD_AntennaOff();
        //PCD_Reset() 
        // PCD_AntennaOn() 
}