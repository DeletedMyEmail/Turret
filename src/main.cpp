#include <Arduino.h>
#include <ESP32Servo.h>
#include "../include/ota-server.h"
#include "../include/WebInterface.h"

#define RELAY_PIN 16
#define SERVO_PIN_SHOT 17
#define SERVO_PIN_X 18
#define SERVO_PIN_Y 19

#define SSID ""
#define PASSWORD ""

aos::WebServer server;
Servo servoX, servoY, servoShot;
unsigned int posX = 90;
unsigned int posY = 90;

void initServer();
void initServos();
void resetServos();

void setup() {
  Serial.begin(250000);
  pinMode(RELAY_PIN, OUTPUT);
  
  initServer();
  initServos();
  resetServos();
}

void loop() {}

void resetServos() {
  servoX.write(90);
  servoY.write(90);
  servoShot.write(4);
}

void initServer() {
  server.asyncWebServer.on("/move", HTTP_PUT, [](AsyncWebServerRequest* req) {
    String newCoords = req->arg("VALUE");
    posX = newCoords.substring(newCoords.indexOf("x:")+2, newCoords.indexOf(",")).toInt();
    posY = newCoords.substring(newCoords.indexOf("y:")+2, newCoords.indexOf("}")).toInt();
    posY = posY < 45 ? 45 : posY > 140 ? 140 : posY;

    servoX.write(posX);
    servoY.write(posY);

    Serial.println("X: " + String(posX) + " Y: " + String(posY));

    req->send(200, "text/plain", "OK");
  });
  server.asyncWebServer.on("/fire", HTTP_PUT, [](AsyncWebServerRequest* req) {
    digitalWrite(RELAY_PIN, HIGH);
    servoShot.write(4);
    delay(250);
    servoShot.write(90);
    delay(180);
    digitalWrite(RELAY_PIN, LOW);
    delay(2000);
    servoShot.write(4);

    req->send(200, "text/plain", "OK");
  });
  server.asyncWebServer.on("/", [](AsyncWebServerRequest* req) {
    req->send(200, "text/html", PAGE_HTML);
  });

  server.begin(SSID, PASSWORD);
}

void initServos() {
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  servoX.setPeriodHertz(50); 
  servoX.attach(SERVO_PIN_X, 500, 2500);
  servoY.setPeriodHertz(50); 
  servoY.attach(SERVO_PIN_Y, 500, 2500);
  servoShot.setPeriodHertz(50); 
  servoShot.attach(SERVO_PIN_SHOT, 500, 2500);
}
