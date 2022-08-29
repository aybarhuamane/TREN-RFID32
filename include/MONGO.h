#include <Arduino.h>
#include <Separador.h>


String separar(String datosrecibidos, int i){
  Separador s;
  String elemento1 = s.separa(datosrecibidos,',',0);
  String elemento2 = s.separa(datosrecibidos,',',1);
  String elemento3 = s.separa(datosrecibidos,',',2);
  String cadenas[]={elemento1,elemento2,elemento3};
 // Serial.println("ELEMENTO SEPARADO1:"+ elemento1);
  
 // Serial.println("ELEMENTO SEPARADO2:"+ elemento2);
  
 // Serial.println("ELEMENTO SEPARADO3:"+ elemento3);
 return cadenas[i];  
} 


void callback_mongo(char* topic, byte* payload, unsigned int length) {

  Serial.print("Path -> ");//Imprime cadena
  Serial.print(topic);//Imprime puntero topic, que apunta a una cadena
  Serial.print("\n");//Imprime cadena espacio
  Serial.print("Payload -> ");//Imprime cadena
  payload[length] = 0;//Coloca un cero al final del byte array para convertirlo en cadena
  Serial.println((char *)payload);//Imprime puntero payload, que apunta a una cadena

  String miTopic = String(topic);//Crea objeto de la clase String con el contenido de topic
  String miPayload = String((char *)payload);//Crea objeto de la clase String con el contenido de payload

  /*
     Permite identificar mediante comparacion si se trata de algun topico subscrito.
  */
if(miTopic.equals("data/encontrado")){  // la data regresa por este tramo
      Serial.println(separar(miPayload,0));
      Serial.println(separar(miPayload,1));
      Serial.println(separar(miPayload,2));
      delay(100); //LUEGO QUITAR 
}

}

