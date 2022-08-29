#include <MFRC522.h>
//#include <RED.h>
#define _CONFIG1 
#define SECONDS 1000UL
#define PERIODO_SENSADO 5*SECONDS   // sensado cada 5 seconds
unsigned long tiempo=0;             // tiempo grabado
byte ActualUID[4];


#if defined _CONFIG1 
        //RFID : SPIClass MRFID(HSPI);  // DENTRO DE LA LIBRERIA MFRC522.cpp
        extern SPIClass MRFID;
        #define RST_PIN_H 27  
        #define SS_PIN_H 2
        #define CLK_PIN_H 14
        #define MOSI_PIN_H 13
        #define MISO_PIN_H 12     

#endif

MFRC522 mfrc522(SS_PIN_H, RST_PIN_H); // Create MFRC522 instance


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

void loop_rfid(){
          

            if (mfrc522.PICC_IsNewCardPresent())
        {
                if (mfrc522.PICC_ReadCardSerial())
                {

                        if (millis() - tiempo > PERIODO_SENSADO)
                        {
                                
                                Serial.println(F("\nCard UID:"));
                                String miActualUID="";
                                for (byte i = 0; i < mfrc522.uid.size; i++)
                                {
                                        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                                        Serial.print(mfrc522.uid.uidByte[i], HEX);
                                        
                                        if(i>=1 || mfrc522.uid.uidByte[i] < 0x10 ){  // Hacemos que no adicione el Espacio " " en el inicio
                                        mfrc522.uid.uidByte[i] < 0x10 ? miActualUID= miActualUID +" 0" : miActualUID=miActualUID+" ";
                                        }
                                        miActualUID = miActualUID  + String(mfrc522.uid.uidByte[i], HEX);
           
                                        //ActualUID[i] = mfrc522.uid.uidByte[i];
                                        
                                }

                                //String miActualUID = String((char *)ActualUID);
                                Serial.println("Se envio:"+ miActualUID);
                                client.publish(TOPICO_PUB_DATA2,miActualUID.c_str()); //CONSULTAMOS A MONGO EL DATO LEIDO
                                tiempo = millis();
                        }
                }
        }
}