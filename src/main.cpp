#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>
#include <ArduinoJson.h>
#include "WebInterface.h"

const char* ssid = "ssid";
const char* password = "password";
WebServer server(80);
String request;

unsigned long prevMillis;
const long timeout = 6000;

Servo hServo, vServo;
int hPos = 0;
int vPos = 0;
bool auto_mode = false;

void sendWebpage();
void hRotate();
void vRotate();
void fire();
void initWifi();
void initServer();
void initServos();

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting...");
  
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

void hRotate() {
  hPos = server.arg("VALUE").toInt();
  Serial.println(hPos);
  hServo.write(hPos);
  server.send(200, "text/plain", String(hPos));
}

void vRotate() {
  vPos = server.arg("VALUE").toInt();
  Serial.println(vPos);
  vServo.write(vPos);
  server.send(200, "text/plain", String(vPos));
}

void fire() {}

void initWifi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  Serial.println();
}

void initServer() {
  server.on("/", HTTP_GET, sendWebpage);
  server.on("/h_pos", HTTP_PUT, hRotate);
  server.on("/v_pos", HTTP_PUT, vRotate);
  server.on("/fire", HTTP_PUT, fire);
  server.begin();
}

void initServos() {
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  hServo.setPeriodHertz(50); 
  hServo.attach(19, 500, 2500);
  vServo.setPeriodHertz(50); 
  vServo.attach(18, 500, 2500);
}
