
#include <Separador.h>


bool act = true;
unsigned long t_m = 0;

//#define ANTIGUO_PY   
#ifndef ANTIGUO_PY
  #define NUEVO_PY
#endif

#ifdef  ANTIGUO_PY
String separar(String datosrecibidos, int i)
{
  Separador s;
  String elemento1 = s.separa(datosrecibidos, ',', 0);
  String elemento2 = s.separa(datosrecibidos, ',', 1);
  String elemento3 = s.separa(datosrecibidos, ',', 2);
  String cadenas[] = {elemento1, elemento2, elemento3};
  // Serial.println("ELEMENTO SEPARADO1:"+ elemento1);

  // Serial.println("ELEMENTO SEPARADO2:"+ elemento2);

  // Serial.println("ELEMENTO SEPARADO3:"+ elemento3);
  return cadenas[i];
}

void callback_mongo(char *topic, byte *payload, unsigned int length)
{

  Serial.print("Path -> ");        // Imprime cadena
  Serial.print(topic);             // Imprime puntero topic, que apunta a una cadena
  Serial.print("\n");              // Imprime cadena espacio
  Serial.print("Payload -> ");     // Imprime cadena
  payload[length] = 0;             // Coloca un cero al final del byte array para convertirlo en cadena
  Serial.println((char *)payload); // Imprime puntero payload, que apunta a una cadena

  String miTopic = String(topic);             // Crea objeto de la clase String con el contenido de topic
  String miPayload = String((char *)payload); // Crea objeto de la clase String con el contenido de payload

  /*
     Permite identificar mediante comparacion si se trata de algun topico subscrito.
  */
  if (miTopic.equals("data/buscar2"))
  {

    act = true;
    t_m = millis();

    //  Serial.println("TARJETA  ACCEDIDA");
   
  }

   else if (miTopic.equals("data/encontrado"))
    { // la data regresa por este tramo
      // Serial.println(separar(miPayload,0));
      // Serial.println(separar(miPayload,1));

      // delay(50); //LUEGO QUITAR
      // analisis
      String uid_bd = separar(miPayload, 0);         // uid
      int status_bd = separar(miPayload, 1).toInt(); // blacklist

      Serial.println(" LOCAL :" + String(miActualUID) + ": RED :" + String(uid_bd) + ":Status:" + String(status_bd));

      
      if (separar(miPayload, 1) == "1") // BLACKLIST
      {
        Serial.println("tarjeta bloqueada");
        //  Serial.print("TARJETA ACEPTADA");
        //  print_lcdc("TARJETA ACEPTADA");

      //digitalWrite(ACT_MONGO, HIGH); //RELAY_NA- sigue abierto
      digitalWrite(ACT_MONGO, LOW); //RELAY_NC 
       act = false;
      }
    t_m = millis();
    }
  }

#elif defined NUEVO_PY
// 26/9/22

void callback_mongo(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Path -> ");        // Imprime cadena
  Serial.print(topic);             // Imprime puntero topic, que apunta a una cadena
  Serial.print("\n");              // Imprime cadena espacio
  Serial.print("Payload -> ");     // Imprime cadena
  payload[length] = 0;             // Coloca un cero al final del byte array para convertirlo en cadena
  Serial.println((char *)payload); // Imprime puntero payload, que apunta a una cadena

  String miTopic = String(topic);             // Crea objeto de la clase String con el contenido de topic
  String miPayload = String((char *)payload); // Crea objeto de la clase String con el contenido de payload

    if (miTopic.equals("data/grab"))
    { // la data regresa por este tramo
    
      if ( miPayload.equals("0"))
      {
        Serial.println("tarjeta No bloqueada \n");
        //RELAY CERRADO
        act =true;
        t_m = millis();
      }
      else if ( miPayload.equals("1")) // BLACKLIST
      {
       
        Serial.println("tarjeta bloqueada \n");
        //  Serial.print("TARJETA ACEPTADA");
        //  print_lcdc("TARJETA ACEPTADA");
       //digitalWrite(ACT_MONGO, HIGH); //RELAY_NA- sigue abierto
       digitalWrite(ACT_MONGO, LOW); //RELAY_NC  ABIERTO
       act = false;
       t_m = millis();
      }

    }

    else if (miTopic.equals("data/grab2"))
    { // la data regresa por este tramo  
    Serial.println("LEER GRAB \n");
      if (miPayload.equals("0"))
      {
        Serial.println("tarjeta No bloqueada2 \n");
        //RELAY CERRADO
        act =true;
        t_m = millis();
      }


    // Serial.println("STADO RELAY: " + String(digitalRead(ACT_MONGO))  );
    //      digitalRead(ACT_MONGO) == 0 ? Serial.println("ABIERTO") : Serial.println("CERRADO") ;
   }
   
      
}
  // END CALLBACK
#endif
void relay_NA()
{     //PIN.h init  LOW = RELAY CERRADO
      if(act){
      digitalWrite(ACT_MONGO, LOW); // CIERRA RFID2
      
    }
        //STADO GENERAL    
          if(millis() - t_m > 1500UL)
      {
          t_m = millis(); // SETEAMOS
          digitalWrite(ACT_MONGO,HIGH); //ABRE RELAY
          act = false;
      }

}


void relay_NC()
{     //PIN.h init  LOW = RELAY CERRADO
      if(act){
      digitalWrite(ACT_MONGO, HIGH); // CIERRA RFID2 SE MANTIENE
      // digitalRead(ACT_MONGO) == 0 ? Serial.println("ABIERTO") : Serial.println("CERRADO") ;
      //despues de 2 segundos se resetea cambia  act = low
    }
      // STADO GENERAL    AL INICIAR DESPUES DE 2SEG SE EJECUTA
          if(millis() - t_m > 1500UL) //EL TIEMPO QUE SE MANTENDRA ABIERTO  LUEGO SE RESETEARA
      {
          t_m = millis(); // SETEAMOS
          digitalWrite(ACT_MONGO,LOW); //ABIERTO RELAY
          //Serial.println("SETEAMOS");
         act = false;
      }
}


