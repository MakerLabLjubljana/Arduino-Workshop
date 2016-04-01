/*
*Telnet chat server
*/

#include <SPI.h> //SPI knjižnica za komunikacijo z Ethernet shieldom
#include <Ethernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xB1};
IPAddress ip(192, 168, 1, 177);

// telnet defaults to port 23
EthernetServer server(23);

void setup() {
  //Init serial
  Serial.begin(9600);
  Serial.println("Serial ready.");
  
  //Init ethernet
  Serial.println("Starting ethernet...");
  if(Ethernet.begin(mac)==0){
    Serial.println("DHCP failed");
    Ethernet.begin(mac,ip);
  }
  delay(1000);
  Serial.println("Ethernet connected!");
  
  Serial.print("Chat server address:");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // wait for a new client:
  EthernetClient client = server.available();
  
  // when the client sends the first byte, say hello:
  if (client) {
    // clear out the input buffer:
    client.flush();

    if (client.available() > 0) {
      // read the bytes incoming from the client:
      char thisChar = client.read();
      // echo the bytes to the server as well:
      Serial.println(client.readString());
    }
  }

}
