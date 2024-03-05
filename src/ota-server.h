#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

namespace aos {
    typedef std::function<void(AsyncWebServerRequest* req)> RequestHandlerFunction;

    struct WebServer {
        AsyncWebServer asyncWebServer;
        
        WebServer(uint16_t port = 80);
        WebServer(AsyncWebServer& server);

        void begin(const char* ssid, const char* password);
    private:
        void initWifi(const char* ssid, const char* password);
    };
}