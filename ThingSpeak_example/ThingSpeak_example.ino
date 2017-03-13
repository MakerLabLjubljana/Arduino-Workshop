#include <SPI.h>
#include <Ethernet.h>

// ETHERNET constants
byte mac[] = {0xD4,0x28,0xB2,0xFF,0xA0,0xA1}; // arduino mac address

// ETHERNET variables
EthernetClient client; // Initialize Arduino Ethernet Client

// ThingSpeak constants
byte postServer[]  = {184,106,153,149}; //ThingSpeak server IP
String writeAPIKey = "<WRITE API KEY>"; //Your channel's write key
const int updateInterval = 15*1000; //Interval in milliseconds

void setup() {
  Serial.begin(9600); //Start serial communication
  //connect arduino to the network
  if(Ethernet.begin(mac) == 0){
    Serial.println("DHCP failed");
  }else{
    Serial.println("DHCP connected");
  }
}

void loop() {
  //Read the sensor value
  String Value0 = String(analogRead(A9));
  Serial.println(Value0);
  Value0 = "field1="+Value0;
  
  //POST the read data to the server
  POST(Value0);
  
  //Wait for server response
  while(!client.available()){}
  //Print the server response to serial
  while(client.available()){
    char c = client.read();
    Serial.print(c);
  }
  
  //Stop the client to prepare for the next connection
  client.stop();
  
  //Wait some time before repeating the process
  delay(updateInterval);
}

void POST(String data){
  if (client.connect(postServer, 80)){ //Connect to the ThingSpeak server
    
    //print a HTTP POST header to the EthernetClient
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+writeAPIKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(data.length());
    client.print("\n\n");
    client.print(data);
    
    //client.flush();
    Serial.println("Data posted");
  }
}
