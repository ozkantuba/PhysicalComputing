

#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

ESP8266WiFiMulti WiFiMulti;

int A;
int B;
int C;
int D;
//#define led 13
const int led = 0;

int latitude1;
int longitude1;


void setup() {

  Serial.begin(115200);
  delay(10);

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("your network's id", "your password");
  
  Serial.println();
  Serial.println("Connecting to WiFi");
  
  while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(300);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(300);

  pinMode (led, OUTPUT);


}

void loop() {

A = random (255);
B = random (255);
C = random (255);
D = random (255);

 digitalWrite(led, LOW);   
 delay(100);                      
 digitalWrite(led, HIGH);  
 delay(100);  
 digitalWrite(led, LOW);   

  
const IPAddress remote_ip(A,B,C,D);

  Serial.println();
  Serial.print("WiFi connected with IP");  
  Serial.println(WiFi.localIP());

  Serial.println(remote_ip);
  Serial.print("Are you there?");

  if(Ping.ping(remote_ip,10)) {
  Serial.println("I'm here");
  digitalWrite(led, HIGH); 
  
  Serial.println("Where are you?");
  
  delay(100);

  Serial.println(String(A)+"."+String(B)+"."+String(C)+"."+String(D));
  HTTPClient http;  //Declare an object of class HTTPClient
 
  http.begin("http://api.ipstack.com/"+String(A)+"."+String(B)+"."+String(C)+"."+String(D)+"?access_key=8319aafe9a0b405bd476c0161d57ad3f");  //Specify request destination
  int httpCode = http.GET();                                                                  //Send the request
 
  if (httpCode > 0) { //Check the returning code
 
  String payload = http.getString();   //Get the request response payload
  Serial.println(payload);        //Print the response payload

  DynamicJsonBuffer jsonBuffer;

  JsonObject& root = jsonBuffer.parseObject(payload);
 latitude1 = root[String("latitude")];
 longitude1 = root[String("longitude")];
 
  Serial.println(latitude1);   
  Serial.println(longitude1);                     
                  

  }else{
  Serial.println("I'm hidding");
  }
 
  http.end();   //Close connection

  delay(300);    //Send a request every 30 seconds
    
  } else {
  Serial.println("I ignore you");
                    
  }

  delay(100);

  

}
