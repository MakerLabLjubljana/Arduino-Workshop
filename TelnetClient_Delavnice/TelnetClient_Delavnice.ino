#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 1, 50);

IPAddress server(10, 60, 60, 216);

// Initialize the Ethernet client library
EthernetClient client;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("Serial ready..");
  // start the Ethernet connection:
  if(Ethernet.begin(mac)==0){
    Serial.println("DHCP failed");
    Ethernet.begin(mac,ip);
  }
  Serial.println("Ethernet connected!");

  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 23)) {
    Serial.println("connected");
  }else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop()
{
  // if there are incoming bytes available
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // as long as there are bytes in the serial queue,
  // read them and send them out the socket if it's open:
  boolean sent = false;
  if(Serial.available() > 0) {
    String toSend = Serial.readString();
    Serial.println(toSend);
    if (client.connected()) {
      client.println(" User 1: "+toSend);
    }
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    // do nothing:
    while (true);
  }
}




