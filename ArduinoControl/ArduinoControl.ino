#include <SPI.h>        
#include <Ethernet.h>
#include <EthernetUdp.h>



// Enter a MAC address and IP address for your controller below.

// The IP address will be dependent on your local network:

byte mac[] = {0x90, 0xA2, 0xDA, 0x0F, 0x2E, 0x26};

IPAddress ip(10, 0, 0, 100);
IPAddress ipserver(10,0,0,16);



unsigned int localPort = 8008;      // local port to listen on



// An EthernetUDP instance to let us send and receive packets over UDP

EthernetUDP Udp;



void setup() {

   Serial.begin(9600);
   Serial.println("UDP Client on port -"+ localPort);

  // start the Ethernet and UDP:

  Ethernet.begin(mac,ip);

  Udp.begin(localPort);

}



void loop() {
  
      Udp.beginPacket(ipserver, localPort);
    
      Udp.write(" jono ");
   
    Udp.endPacket();
    
    delay(5000);

}

