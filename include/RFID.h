#include <MFRC522.h>
#include <Arduino.h>
//#include <RED.h>

#define SECONDS 1000UL
#define PERIODO_SENSADO 1*SECONDS   // sensado cada 5 seconds
unsigned long tiempo=0;             // tiempo grabado

int codigo;
byte ActualUID[4];

String miActualUID;
String miActualUID_DEC;

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
                                miActualUID="";                         //limpia el UID


                                for (byte i = 0; i < mfrc522.uid.size; i++)
                                {
                                        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                                        Serial.print(mfrc522.uid.uidByte[i], HEX);
                                        
                                        if(i>=1 || mfrc522.uid.uidByte[i] < 0x10 ){  // Hacemos que no adicione el Espacio " " en el inicio
                                        mfrc522.uid.uidByte[i] < 0x10 ? miActualUID= miActualUID +" 0" : miActualUID=miActualUID+"";//" "; //SIN SPACIOS
                                        }
                                        miActualUID = miActualUID  + String(mfrc522.uid.uidByte[i], HEX);

                                        //ActualUID[i] = mfrc522.uid.uidByte[i];
                                        //digitalWrite(ACT_MONGO, HIGH );       
                                }

                                //String miActualUID = String((char *)ActualUID);
                                
                                 
                                //Serial.println("\nSe envio:"+ miActualUID);
                                uint32_t dec32u = strtoul(miActualUID.c_str(), NULL, 16);
                                 miActualUID_DEC = String(dec32u, DEC); // DATO EN DECIMA
                                 Serial.println("\n Se envio:" + miActualUID_DEC);
                                client.publish(TOPICO_PUB_DATA3,miActualUID_DEC.c_str()); //CONSULTAMOS A MONGO EL DATO LEIDO
                                tiempo = millis();
                                               
                              // bocina(1);// HACE RETARDO
                        }

                }
        }
}