#include <UIPEthernet.h>
#include <UIPServer.h>
#include <UIPClient.h>

UIPServer server = UIPServer(1883);
#define MYIPADDR 10,10,0,44
#define MYIPMASK 255,255,255,0
#define MYDNS 10,10,0,1
#define MYGW 10,10,0,1

void setup() {

  uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};
  IPAddress myIP(10,10,0,43);
  IPAddress myDNS(10,10,0,1);
  UIPEthernet.init(33);
  UIPEthernet.begin(mac,myIP,myDNS);

  server.begin();
}

void loop() {

  if (UIPClient client = server.available()) {
    if (client) {
      while (client.available()) {
        int c = client.read();
        client.write(c);
      }
    }
  }
}