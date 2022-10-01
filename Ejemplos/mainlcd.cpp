#include <Arduino.h>
// entradas
#define RB1 // OPAMS
#define RB3  17// TRANSISTORES SALDO
#define RB4 // OPAMS
#define RB7 16 // TRANSISTORES RED
// salidas 
#define RB0
#define RB5
int incremento =0;
#include "Wire.h"
#include "LiquidCrystal_I2C.h"
//#define SCL 22
//#define SDA 21
LiquidCrystal_I2C lcd(0x27, 20, 4); 
void setup()
{

    Serial.begin(115200);
    
    // pinMode(RB7,OUTPUT);  //EL PIC RECIVE
    // pinMode(RB3,OUTPUT);  //EL PIC RECIVE
  lcd.init();
 lcd.backlight();

  //lcd.setBacklight((uint8_t)1);
  lcd.setCursor(1, 0);
  lcd.print("This is erick");
  lcd.setCursor(2, 2);
  delay(700);

   lcd.clear();
}

void suspensivos_lcd(int valor,String puntos)
{

  if(0 < valor)
  { 
    //lcd.clear();
        puntos = puntos + '.';

  }
        
        lcd.setCursor(valor,0);
        lcd.print(puntos);
        
}


void loop(){
  // lcd.setCursor(1, 0);
  // lcd.print("This is erick");
  // lcd.setCursor(2, 2);


    // digitalWrite(RB3,HIGH);
    // digitalWrite(RB7,HIGH);
    // Serial.println("ON");
    // delay(5000);
    // digitalWrite(RB3,LOW);
    // digitalWrite(RB7,LOW);
    //  Serial.println("OFF");
    // delay(5000);
    incremento +=1;
    
//suspensivos_lcd(incremento,"hola" ,".");
 delay(1000);
}


