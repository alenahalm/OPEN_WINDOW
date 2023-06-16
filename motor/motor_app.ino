#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <AccelStepper.h>

// #define MotorInterfaceType 4
AccelStepper stepper = AccelStepper(4, 5,4, 14, 12);

int count_rotate = 0;

int OpenFunction(){
  stepper.setCurrentPosition(count_rotate);
  Serial.println("OPEN");
  while (stepper.currentPosition() != 1800) {
    stepper.setSpeed(900);
    stepper.runSpeed();
  }
  return (count_rotate);
}

int CloseFunction(){
  stepper.setCurrentPosition(count_rotate);
Serial.println("CLOSE");
  while (stepper.currentPosition() != -1800) {
    stepper.setSpeed(-900);
    stepper.runSpeed();
  }
  return (count_rotate);
}
ESP8266WebServer server(80);

const char* name = "alena";
const char* password = "wtnw4630";

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(name, password);
  stepper.setMaxSpeed(1000);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  
  Serial.println(WiFi.localIP());

  server.on("/open", OpenFunction);
  server.on("/close", CloseFunction);

  server.begin();
}

void loop() {

  server.handleClient();
  delay(1);

}