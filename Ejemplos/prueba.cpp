#include "PIN.h"

void setup()
{
    
    Serial.begin(115200);
    PINES();
    pinMode(15,OUTPUT);
    pinMode(22,OUTPUT);
}

void loop()
{

digitalWrite(ALERTA,HIGH);
digitalWrite(15,HIGH);
digitalWrite(22,HIGH);
Serial.println("encendido");
delay(3000);
digitalWrite(ALERTA,LOW);
digitalWrite(15,LOW);
digitalWrite(22,LOW);
Serial.println("apagado");
delay(3000);



}