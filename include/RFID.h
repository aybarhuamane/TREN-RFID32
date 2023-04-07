#include <MFRC522.h>
#include <Arduino.h>
//#include <RED.h>

#define SECONDS 1000UL
#define PERIODO_SENSADO 1.5*SECONDS   // sensado cada 5 seconds
unsigned long tiempo=0;             // tiempo grabado
char* data[4];
int codigo;
byte ActualUID[4];


String miActualUID;
String miActualUID_DEC;
String cargo = "";
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

void antena_off()
{
        mfrc522.PCD_AntennaOff();
        //PCD_Reset() 
        // PCD_AntennaOn() 
}

void antena_on()
{
        mfrc522.PCD_AntennaOn();
        //PCD_Reset() 
        // PCD_AntennaOn() 
}

void decidir_rfid()
{


        
        if(stanby == true)
        {
            mfrc522.PCD_AntennaOn();

        }
        else if(stanby == false)
        {
                mfrc522.PCD_AntennaOff();
        }

}

void loop_rfid(){
          

            if (mfrc522.PICC_IsNewCardPresent())
        {
                if (mfrc522.PICC_ReadCardSerial())
                {

                        if (millis() - tiempo > PERIODO_SENSADO)
                        {
                                
                                //Serial.println(F("\nCard UID:"));
                                cargo="";                         //limpia el UID

                                
                                // for (byte i = 0; i < mfrc522.uid.size; i++)
                                // {
                                //       //  Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                                //       //  Serial.print(mfrc522.uid.uidByte[i], HEX);
                                        
                                //         if(i>=1 || mfrc522.uid.uidByte[i] < 0x10 ){  // Hacemos que no adicione el Espacio " " en el inicio
                                //         mfrc522.uid.uidByte[i] < 0x10 ? miActualUID= miActualUID +" 0" : miActualUID=miActualUID+"";//" "; //SIN SPACIOS
                                //         }
                                //         miActualUID = miActualUID  + String(mfrc522.uid.uidByte[i], HEX);

                                //         ActualUID[i] = mfrc522.uid.uidByte[i];
                                //         //digitalWrite(ACT_MONGO, HIGH );       
                                // }


                  Serial.println("Card UID:");




                //   for (byte i = 0; i < mfrc522.uid.size; i++) {
                //         //  Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                //         //  Serial.print(mfrc522.uid.uidByte[i], HEX);  
                //          if(i>=1 || mfrc522.uid.uidByte[i] < 0x10 ){  // Hacemos que no adicione el Espacio " " en el inicio
                //                          mfrc522.uid.uidByte[i] < 0x10 ? miActualUID= miActualUID +" 0" : miActualUID=miActualUID+"";//" "; //SIN SPACIOS
                                         
                //                   }
                //                   //miActualUID = miActualUID  + String(mfrc522.uid.uidByte[i], HEX);
                //                  miActualUID = miActualUID  + String(mfrc522.uid.uidByte[i], HEX);
                //                  //  miActualUID = mfrc522.uid.uidByte[i];
                //                    //Serial.println((miActualUID,HEX));
                                  
                //          }

                  for (byte i = 0; i < mfrc522.uid.size; i++) {

                                if(mfrc522.uid.uidByte[i] < 0x10)
                                {
                                  // mfrc522.uid.uidByte[i] < 0x10 ? cargo += " 0" : cargo += " ";
                                   cargo += ",0";
                                } 
                                else{
                                     cargo += ",";
                                }

                               cargo = cargo + String(mfrc522.uid.uidByte[i],HEX);
                                // (mfrc522.uid.uidByte[i], HEX);
                                //  Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                                //   Serial.print(mfrc522.uid.uidByte[i], HEX); 
                                //   ActualUID[i] = (mfrc522.uid.uidByte[i], HEX);
                                  //SActualUID = mfrc522.uid.uidByte[i];
                         }

                             Separador s;
                             String elemento1 = s.separa(cargo, ',', 1);
                             String elemento2 = s.separa(cargo, ',', 2);
                             String elemento3 = s.separa(cargo, ',', 3);
                             String elemento4 = s.separa(cargo, ',', 4);
                            
                               
                                String miActual = elemento4 + elemento3 +elemento2 +elemento1; 
                                //Serial.println(mfrc522.uid.uidByte[2],HEX);

                                        Serial.println(miActual);
                                //String miActualUID = String((char *)ActualUID);
                               // Serial.println("Se envio:"+ mfrc522.uid.uidByte);
                                //]******
                                // Serial.println( mfrc522.uid.uidByte[2],HEX);
                                // Serial.println( SActualUID[2]);

                               // Serial.println("\nSe envio hex:"+ String(mfrc522.uid.uidByte[0],HEX) +","+ String(mfrc522.uid.uidByte[1],HEX)+"," + String(mfrc522.uid.uidByte[2],HEX)+"," + String(mfrc522.uid.uidByte[3],HEX) );
                               
                             //  String miActual =  String(mfrc522.uid.uidByte[3],HEX) + String(mfrc522.uid.uidByte[2],HEX)+ String(mfrc522.uid.uidByte[1],HEX)+ String(mfrc522.uid.uidByte[0],HEX) ;
                                //***********************************************************
                                    uint32_t dec32u = strtoul(miActual.c_str(), NULL, 16);
                                   miActualUID_DEC = String(dec32u, DEC); 
                                Serial.println("\n Se envio:" + String(TOPICO_PUB_DATA1)+ " " + miActualUID_DEC);
                                client.publish(TOPICO_PUB_DATA1,miActualUID_DEC.c_str()); //CONSULTAMOS A MONGO EL DATO LEIDO
                                tiempo = millis();
                               // mfrc522.PICC_HaltA();

                                               
                              // bocina(1);// HACE RETARDO
                        }
                        
                }
        }
}