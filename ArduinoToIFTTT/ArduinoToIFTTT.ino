#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFF, 0xED };

char server[] = "maker.ifttt.com"; 
IPAddress ip(10, 0, 0, 99);
EthernetClient client;

String IFTTTKey = "<YOUR IFTTT KEY>";
String TriggerWord = "<YOUR TRIGGER WORD>";

void setup() {
  Serial.begin(9600);

  while (!Serial) {
    ; 
  }

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }

  POSTrequest();
}

void loop() {
  
}

String getJSON() {
  String json = "{\"value1\":\"";
  json += 0;
  json += "\",\"value2\":\"";
  json += 0;
  json += "\",\"value3\":\"";
  json += 0;
  json += "\"}";

  return json;
}

int POSTrequest(){
  Serial.println("connecting...");
  
  if (client.connect(server, 80)) {
    Serial.println("connected");

    String json = getJSON();
  
    client.println("POST http://maker.ifttt.com/trigger/"+TriggerWord+"/with/key/"+IFTTTKey+" HTTP/1.1");
    client.println("Host: maker.ifttt.com");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(json.length());
    client.println("Connection: close");
    client.println();
    client.println(json);
    client.println();

  } else {
    Serial.println("connection failed");
  }
  delay(500);

  while (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  Serial.println("disconnecting.");
  client.stop();
}
