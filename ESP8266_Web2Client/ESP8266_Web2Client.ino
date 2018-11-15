/*********

PHYSICAL COMPUTING FALL 2018 - PARSONS DT
by Tuba Ozkan

1)
Go over the code line by line with your friend and debug the code;

Try to understand who is the server, and who is the client in this context. 
Try to use a different sensor and develop a new project. 
What does client.read reads?
What does blank_line boolean does?

2)
Add another sensor to your circuit. 
Read and publish data into the website

BONUS:
Try to combine this with clientToServer code from last week.
As an example, you can try to control an LED through the website, 
while sending sensor data to the website.

*********/

#include <Wire.h>
#include <ESP8266WiFi.h>

// Replace with your network details
const char* ssid = "ssid";
const char* password = "password";

int analogpot = 17;
String myPotString;

// Web Server on port 80
WiFiServer server(80);

// only runs once on boot
void setup() {
  // Initializing serial port for debugging purposes
  Serial.begin(115200);
  delay(10);
  
  pinMode(analogpot, INPUT);
  Wire.setClock(100000);
  
  // Connecting to WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Starting the web server
  server.begin();
  Serial.println("Web server running. Waiting for the ESP IP...");
  delay(10000);
  
  // Printing the ESP IP address
  Serial.println(WiFi.localIP());

}

//define a function for reading sensor's data
void getData() {
    int potValue = analogRead(analogpot)/4;
    //stringfying integer value;
    myPotString = String(potValue);
    delay(100);
 
}

// runs over and over again
void loop() {
  // Listenning for new clients, this is essential for sending data to the client side.
  WiFiClient client = server.available();

  // this statement loops only when there is a request from the client side.
  if (client) {
    Serial.println("New client");
    // bolean to locate when the http request ends
    boolean blank_line = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        
        if (c == '\n' && blank_line) {
            getData();
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();
            // your actual web page that displays sensor data
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<head><META HTTP-EQUIV=\"refresh\" CONTENT=\"15\"></head>");
            client.println("<body><h1>ESP8266 Sensor Data - Web Server</h1>");
            client.println("<table border=\"2\" width=\"456\" cellpadding=\"10\"><tbody><tr><td>");
            client.println("<h3>potValue = ");
            client.println(myPotString); 
            break;
        }
        if (c == '\n') {
          // when starts reading a new line
          blank_line = true;
        }
        else if (c != '\r') {
          // when finds a character on the current line
          blank_line = false;
        }
      }
    }  
    // closing the client connection
    delay(1);
    client.stop();
    Serial.println("Client disconnected.");
  }
} 
