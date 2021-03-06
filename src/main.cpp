#include "main.h"

void setup()
{
  Serial.begin(115200);
  outln("Starting");
  //displaySetup();
  outln("Displaying Splash Screen");

  // Setup all the pins
  pinSetup(); 

  wifiManagerSetup(); // WiFi Manager, SPIFF uploader, OTA Updates

   // Web Server Root URL
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });
  
  server.serveStatic("/", SPIFFS, "/");

  AsyncElegantOTA.begin(&server);
  
  /* *********** start websocket server  ************
  bind a handling function to our websocket endpoint, 
  in order for our code to run when a websocket event occurs.
  We do this by calling the onEvent method on our AsyncWebSocket object.
   initializes the WebSocket protocol.
  */
  ws.onEvent(onEvent);
  server.addHandler(&ws);

  server.begin();
  TelnetServer.begin();

  digitalWrite(LED_BUILTIN, LOW);

  dhtSetup();

}
String previousState = "off";
unsigned long testtimer = millis();
void loop()
{
  wifiManagerLoop();
  AsyncElegantOTA.loop();
  telnetLoop();
  ws.cleanupClients();
  
  getDHTReadings();
  
  if (plugStatus1 == "on") digitalWrite(AC1, LOW);
  else digitalWrite(AC1, HIGH);
  if (plugStatus2 == "on")  digitalWrite(AC2, LOW);
  else digitalWrite(AC2, HIGH);

  //Slider update
  ledcWrite(ledChannel1, dutyCycle1);
  ledcWrite(ledChannel2, dutyCycle2);
}

/*Note that we all call the cleanupClients() method. Here’s why 
  (explanation from the ESPAsyncWebServer library GitHub page):
  Browsers sometimes do not correctly close the WebSocket connection, 
  even when the close() function is called in JavaScript. 
  This will eventually exhaust the web server’s resources and will cause the server to crash.
  Periodically calling the cleanupClients() function from the main loop()limits the number 
  of clients by closing the oldest client when the maximum number of clients has been exceeded.
  This can be called every cycle, however, if you wish to use less power, then calling as infrequently
  as once per second is sufficient.
  */