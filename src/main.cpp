#include <Arduino.h>
#include <WebServer.h>

const char* SSID = "Baldwin";
const char* PASSWORD = "4696301617";

WebServer server(80);

void fanOn() {
  Serial.println("Turning fan on...");
  server.send(200, "text/plain", "Fan is on.");
}

void fanOff() {
  Serial.println("Turning fan off...");
  server.send(200, "text/plain", "Fan is off.");
}

void resDefault() {
  server.send(200, "text/plain", "Hello world!");
}

void connectWiFi() {
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.print("Local IP: ");
  Serial.print(WiFi.localIP());
}

void initRoutes() {
  server.on("/on", fanOn);
  server.on("/off", fanOff);
  server.on("/", resDefault);

  server.begin();
}

void setup() {
  Serial.begin(9600);
  connectWiFi();
  initRoutes();
}

void loop() {
  server.handleClient();
}