#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>
#include <ArduinoJson.h>
#include "WebInterface.h"

#define SERVO_PIN_1 18
#define SERVO_PIN_2 19
#define SSID ""
#define PASSWORD ""

WebServer server(80);
String request;

Servo servoX, servoY;
bool auto_mode = false;
int posX = 0;
int posY = 0;

void sendWebpage();
void moveTurret();
void enableAutoMode();
void fire();
void initWifi();
void initServer();
void initServos();

void setup() {
  Serial.begin(250000);
  delay(1000);
  
  initWifi();
  initServer();
  initServos();
}

void loop() {
  server.handleClient();
}

void sendWebpage() {
  server.send(200, "text/html", PAGE_HTML);
}

void moveTurret() {
  String value = server.arg("VALUE");
  
  posX = value.substring(value.indexOf("x:")+2, value.indexOf(",")).toInt();
  posY = value.substring(value.indexOf("y:")+2, value.indexOf("}")).toInt();
  
  servoX.write(posX);
  servoY.write(posY);

  Serial.println("X: " + String(posX) + " Y: " + String(posY));
  server.send(200, "text/plain", "OK");
}

void fire() {}

void enableAutoMode() {
  server.send(200, "text/plain", "OK");
}

void initWifi() {
  WiFi.begin(SSID, PASSWORD);
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to the WiFi network. IP Address: " + WiFi.localIP().toString());
}

void initServer() {
  server.on("/", HTTP_GET, sendWebpage);
  server.on("/move", HTTP_PUT, moveTurret);
  server.on("/fire", HTTP_PUT, fire);
  server.on("/auto_mode", HTTP_PUT, enableAutoMode);
  server.begin();
}

void initServos() {
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  servoX.setPeriodHertz(50); 
  servoX.attach(SERVO_PIN_1, 500, 2500);
  servoY.setPeriodHertz(50); 
  servoY.attach(SERVO_PIN_2, 500, 2500);
}
