#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "Sensor.h"
#include "Display.h"

ESP8266WebServer server(80);

const char* name = "alena";
const char* password = "wtnw4630";

void getData() {
  getValues();
  String response = "{\"co2\":" + String(CO2) + ", \"temp\":" + String(temp) + "}";
  display_put_txt("T: " + String(temp) + " CO2: " + String(CO2));
  Serial.println("T: " + String(temp) + " CO2: " + String(CO2));
  server.send(200, "application/json", response);
}

void setup() {

  sensor_init();
  display_init();

  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.begin(name, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  
  Serial.println(WiFi.localIP());

  server.on("/data", getData);

  server.begin();
 
}

void loop() {

  server.handleClient();
  delay(1);

}