#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <controller.h>

#define WIFI_SSID "FBI Surveillance Van"
#define WIFI_PASSWORD "DVUKBHIS"
#define WIFI_TIMEOUT 30000

#define SERVER_PORT 1612

#define LED_PIN 16
#define LED_COUNT 61

IPAddress ip(192, 168, 0, 98);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

Controller controller(LED_COUNT, LED_PIN, NEO_BRG + NEO_KHZ800);
WiFiUDP server;

void wifi_setup();

void setup()
{
    controller.init();
    
    Serial.begin(9600);
    wifi_setup();
    server.begin(SERVER_PORT);
}

void loop()
{
    int packetSize = server.parsePacket();
    if(packetSize)
    {
        char *data = new char[packetSize];
        int len = server.read(data, packetSize);
        if(data[0] == 1 && len >= 4)
        {
            controller.setColor(data[1], data[2], data[3]);
        }
        else if(data[0] == 2 && len >= 5)
        {
            controller.setColor(data[1], data[2], data[3], data[4]);
        }
        else if(data[0] == 3 && len >= controller.numPixels() * 3 + 1)
        {
            for(int i=0; i<controller.numPixels(); i++)
            {
                int index = i*3 + 1;
                controller.setColor(i, data[index], data[index+1], data[index+2]);
            }
        }
        else if(data[0] == 4)
        {
        }
        delete data;
    }
    controller.service();
}

void wifi_setup()
{
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    WiFi.mode(WIFI_STA);
    WiFi.config(ip, gateway, subnet);

    unsigned long connect_start = millis();
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        if (millis() - connect_start > WIFI_TIMEOUT)
        {
            Serial.println();
            Serial.print("Tried ");
            Serial.print(WIFI_TIMEOUT);
            Serial.print("ms. Resetting ESP now.");
            ESP.reset();
        }
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println();
}