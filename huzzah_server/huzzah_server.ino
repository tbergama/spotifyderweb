#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid     = "ssid";
const char* password = "password";

// State variables
String message;

ESP8266WebServer server(80);
 
String webString="";     // String to display
// Generally, you should use "unsigned long" for variables that hold time
 
void handle_root() {
  server.send(200, "text/plain", "SpotifyDerweb, change message with /changeMessage\n");
  delay(100);
}
 
void setup(void)
{
  // You can open the Arduino IDE Serial Monitor window to see what the code is doing
  Serial.begin(115200);  // Serial connection from ESP-01 via 3.3v console cable

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.print("\n\r \n\rWorking to connect");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Welcome to SpotifyDerweb!");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
   
  server.on("/", handle_root);

  server.on("/changeMessage", [](){
    setmessage();
    delay(100);
  });

  server.on("/getMessage", [](){
    getmessage();
  });

  message = "Default message\n";
  
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void)
{
  server.handleClient();
}

void setmessage() {
  if (server.hasArg("plain")== false){ //Check if body received
  
        server.send(200, "text/plain", "Body not received");
        return;
  }

  Serial.println("Message Recieved!");
  message = server.arg("plain")+"\n";
}

void getmessage() {
  server.send(200, "text/plain", message);
  Serial.println(message);
}
