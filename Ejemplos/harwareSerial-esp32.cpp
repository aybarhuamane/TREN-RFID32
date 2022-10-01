#include <HardwareSerial.h>
//DOCUMENTATION https://www.esp32.com/viewtopic.php?t=10300
HardwareSerial SerialTFMini( 1 );
HardwareSerial Serial2E( 2 );
////// serial(1) = pin27=RX green, pin26=TX white
////// serial(2) = pin16=RXgreen , pin17=TX white
#define SerialDataBits 115200
void setup()
{
  Serial2E.begin( SerialDataBits );
  SerialTFMini.begin(  SerialDataBits, SERIAL_8N1, 27, 26 );
  }

