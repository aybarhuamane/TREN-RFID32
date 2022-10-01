
/*
LCD :   vcc = +5v
        GND = GND
        SDA =       - convert status logic: 3.3v a 5v
        SCL =       - convert status logic: 3.3v a 5v
*/


#include <Arduino.h>
// // entradas
// #define RB1 // OPAMS
// #define RB3  17// TRANSISTORES SALDO
// #define RB4 // OPAMS
// #define RB7 16 // TRANSISTORES RED
// // salidas 
// #define RB0
// #define RB5
#include "Wire.h"
#include "LiquidCrystal_I2C.h"
//#define SCL 22
//#define SDA 21
LiquidCrystal_I2C lcd(0x27, 20, 4); 

void init_lcd (const char *lcde,int time) //in seconds
{
lcd.clear();
 lcd.init();
 lcd.backlight();

  //lcd.setBacklight((uint8_t)1);
  lcd.setCursor(1, 0);
  lcd.print(lcde);
  delay(time*1000);
  lcd.clear();
}

void  print_lcd(const char *lcde)
{
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print(lcde);
  //lcd.clear();      




    // digitalWrite(RB3,HIGH);
    // digitalWrite(RB7,HIGH);
    // Serial.println("ON");
    // delay(5000);
    // digitalWrite(RB3,LOW);
    // digitalWrite(RB7,LOW);
    //  Serial.println("OFF");
    // delay(5000);

}



void  print_lcdc(const char *lcde)
{      lcd.clear(); 
  lcd.setCursor(2, 1);
  lcd.print(lcde);
  
}
void suspensivos_lcd(int valor,String print )
{

  if(0 < valor)
  { 
        print = print + '.';
        lcd.setCursor(2, 0);
        lcd.print(print);
  }
  
}

