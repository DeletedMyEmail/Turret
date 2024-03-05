#include "../include/ota-server.h"

aos::WebServer::WebServer(uint16_t port) : asyncWebServer(port) {}
aos::WebServer::WebServer(AsyncWebServer& server) : asyncWebServer(server) {}

void aos::WebServer::initWifi(const char* ssid, const char* password) {
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nIP address: " + WiFi.localIP().toString());
}

void aos::WebServer::begin(const char* ssid, const char* password) {
    initWifi(ssid, password);
    AsyncElegantOTA.begin(&asyncWebServer);
    asyncWebServer.begin();
}
