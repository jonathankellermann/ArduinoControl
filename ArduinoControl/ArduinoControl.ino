#include <SPI.h>        
#include <Ethernet.h>
#include <EthernetUdp.h>



// Enter a MAC address and IP address for your controller below.

// The IP address will be dependent on your local network:

byte mac[] = {0x90, 0xA2, 0xDA, 0x0F, 0x2E, 0x26};

IPAddress ip(10, 0, 0, 100);
IPAddress ipserver(10,0,0,16);

int incomingByte=0;

unsigned int localPort = 8008;      // local port to listen on



// An EthernetUDP instance to let us send and receive packets over UDP

EthernetUDP Udp;

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,

void setup() {

   Serial.begin(9600);
   Serial.print("UDP Client on port -");
   Serial.println(localPort);
  // start the Ethernet and UDP:

  Ethernet.begin(mac,ip);

  Udp.begin(localPort);

}



void loop() {
  
     
     // send data only when you receive data:
        if (Serial.available() > 0) {
           Udp.beginPacket(ipserver, localPort);
                // read the incoming byte:
                incomingByte = Serial.read();

                // say what you got:
                Serial.print("I received: ");
                Serial.println(incomingByte, DEC);
                Udp.write(incomingByte);
                Udp.endPacket();
  delay(300);
                // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if(packetSize)
  {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remote = Udp.remoteIP();
    for (int i =0; i < 4; i++)
    {
      Serial.print(remote[i], DEC);
      if (i < 3)
      {
        Serial.print(".");
      }
    }
    Serial.print(", port ");
    Serial.println(Udp.remotePort());
  }
    // read the packet into packetBufffer
    Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
    Serial.println("Contents:");
    Serial.println(packetBuffer);
    
    delay(300);
    
        }
      
    

}

