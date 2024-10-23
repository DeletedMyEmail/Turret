#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <ElegantOTA.h>

namespace aos {
    typedef std::function<void(AsyncWebServerRequest* req)> RequestHandlerFunction;

    struct WebServer {
        AsyncWebServer asyncWebServer;
        
        WebServer(uint16_t port = 80);
        WebServer(const AsyncWebServer& server);

        void begin(const char* ssid, const char* password);
    private:
        static void initWifi(const char* ssid, const char* password);
    };
}