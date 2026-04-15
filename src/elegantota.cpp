#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ElegantOTA.h>

const char *ssid = "Pump_controller";
const char *password = "80100000";
boolean update = false;

WebServer server(80);

unsigned long ota_progress_millis = 0;

void onOTAStart()
{
    // Логирование начала OTA-обновления
    Serial.println("OTA update started!");
    // <Добавьте здесь свой код>
}

void onOTAProgress(size_t current, size_t final)
{
    // Логирование каждую секунду
    if (millis() - ota_progress_millis > 1000)
    {
        ota_progress_millis = millis();
        Serial.printf("OTA Progress Current: %u bytes, Final: %u bytes\n", current, final);
    }
}

void onOTAEnd(bool success)
{
    // Логирование завершения OTA-обновления
    if (success)
    {
        Serial.println("OTA update finished successfully!");
    }
    else
    {
        Serial.println("There was an error during OTA update!");
    }
    // <Добавьте здесь свой код>
}

void ota_setup(void)
{
    if (!WiFi.softAP(ssid, password))
    {
        Serial.print(".");
        while (1)
            ;
    }

    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    server.on("/", []()
              { server.send(200, "text/plain", "Hi! This is ElegantOTA Demo."); });

    ElegantOTA.begin(&server); // Запуск ElegantOTA
                               // Обратные вызовы ElegantOTA
    ElegantOTA.onStart(onOTAStart);
    ElegantOTA.onProgress(onOTAProgress);
    ElegantOTA.onEnd(onOTAEnd);

    server.begin();
    Serial.println("HTTP server started");
    update = true;
}

void ota_loop(void)
{
    if (update)
    {
        server.handleClient();
        ElegantOTA.loop();
    }
}
