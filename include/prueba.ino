
#include <SPI.h>
#include <UIPEthernet.h>
#include <UIPServer.h>
#include <UIPClient.h>
 uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x02};
 IPAddress myIP(10,10,19,20);  //10.52  libre
 IPAddress myDNS(10,10,19,1);
 IPAddress gw(10,10,19,1);
 IPAddress sn(255,255,0,0);

 void setup()
{

    Serial.begin(115200);
    
   // bocina(4);
   // main_ethernet();

 //SI SE CONECTA A LA RED CORRECTAMENTE  TITILEA 3 VECES
    
      UIPEthernet.init(33);
      UIPEthernet.begin(mac,myIP,myDNS, gw, sn);
     // UIPEthernet.begin(mac,myIP,myDNS);
 

  if (UIPEthernet.linkStatus() == LinkON)
  {
    Serial.println("conexion correcta");
  }
  else if (Ethernet.linkStatus() == LinkOFF)
     {
         Serial.println("Ethernet cable is not connected."); 
     }

}