

bool suena = true;

#define PERIODO_INDICADOR_ON 2000UL
#define PERIODO_INDICADOR_OFF 5000UL
#define PERIODO_INDICADOR_INC 5000UL
unsigned long INDICADOR_t=0;
// otros


void parpadeo(bool ENABLE){


//Serial.println("Reiniciando por fallo MQTT SERVER...");
 if( (millis() - INDICADOR_t > PERIODO_INDICADOR_ON)  &&  ENABLE == true)
 {  
    INDICADOR_t = millis();
    // digitalWrite(IND1_MOONGO ,HIGH);
    //  delay(5);
    //  digitalWrite(IND1_MOONGO ,LOW);

    //digitalRead(IND1_MOONGO) == true ? digitalWrite(IND1_MOONGO ,false) : digitalWrite(IND1_MOONGO ,true);
    digitalRead(IND1_MOONGO) == HIGH ? digitalWrite(IND1_MOONGO ,LOW) : digitalWrite(IND1_MOONGO ,HIGH);
    
 }

else if (ENABLE == false)
{
    digitalWrite(IND1_MOONGO ,HIGH);
}

}
void bocina(int cantidad){

    for (int x=0; x < cantidad ; x++){
    Serial.println("SONANDO");
    digitalWrite(BUZZER,HIGH);
    delay(500);
    digitalWrite(BUZZER,LOW);
    delay(500);
    }
}