#include <ESP8266WiFi.h>
#include <WiFiClient.h>

//ESP Web Server Library to host a web page
#include <ESP8266WebServer.h>

//---------------------------------------------------------------
//Our HTML webpage contents in program memory
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>
<center>
<h1>Directie masina</h1><br>
Ciclk to turn <a href="Fata">Fata</a><br>
Ciclk to turn <a href="Spate">Spate</a><br>
Ciclk to turn <a href="Stanga">Stanga</a><br>
Ciclk to turn <a href="Dreapta">Dreapta</a><br>
Click to stop <a href="Stop">Stop</a><br>
<hr>

</center>

</body>
</html>
)=====";
//---------------------------------------------------------------

//SSID and Password of your WiFi router
const char* ssid = "AIA";
const char* password = "UPT-aia!";

//Declare a global object variable from the ESP8266WebServer class.
ESP8266WebServer server(80); //Server on port 80

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 Serial.println("You called root page");
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void handleFata() { 
 Serial.println("F");
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send ADC value only to client ajax request
 
}

void handleSpate() { 
 Serial.println("B");
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send ADC value only to client ajax request
}

void handleStanga() { 
 Serial.println("L");
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send ADC value only to client ajax request
}

void handleDreapta() { 
 Serial.println("R");
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send ADC value only to client ajax request
}

void handleStop()
{
  Serial.println("Stop");
  String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send ADC value only to client ajax request

}


//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
 // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
//If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP

server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
server.on("/Fata",handleFata);
server.on("/Spate",handleSpate);
server.on("/Stanga",handleStanga);
server.on("/Dreapta",handleDreapta);
server.on("/Stop",handleStop);

server.begin();                  //Start server
  Serial.println("HTTP server started");
}

//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient();          //Handle client requests
}
