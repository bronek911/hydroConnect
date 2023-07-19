#include <ESP8266WebServer.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <ArduinoJson.h>
#include <LittleFS.h>
#include <ESP8266WiFi.h>
#include <FS.h>
#include <uri/UriBraces.h>
#include <uri/UriRegex.h>

#include "Relay.h"
#include "Box.h"

/*********
  Author: Michał Bronowski
*********/

// Set web server port number to 80
ESP8266WebServer server(80);

WiFiManager wifiManager;

// Box box(1, "timer", D1, D3);
Box Boxes[1] = {Box("1", "box-1", D1, D3)};

const IPAddress staticIP(192, 168, 55, 126);
const IPAddress gatewayIP(192, 168, 55, 1);
const IPAddress subnetMask(255, 255, 255, 0);

Box *getBoxByName(String name); // convert the file extension to the MIME type
String getContentType(String filename); // convert the file extension to the MIME type
bool handleFileRead(String path);       // send the right file to the client (if it exists)

void setup()
{
    Serial.begin(115200);

    wifiManager.setSTAStaticIPConfig(staticIP, gatewayIP, subnetMask);

    // Mount the LittleFS file system
    if (!LittleFS.begin())
    {
        Serial.println("Failed to mount LittleFS");
        return;
    }

    // fetches ssid and pass from eeprom and tries to connect
    // if it does not connect it starts an access point with the specified name
    wifiManager.autoConnect("HydroConnect");

    // if you get here you have connected to the WiFi
    Serial.println("Connected.");

    server.on("/", handleDashboard);
    server.on("/devices", handleDevices);

    server.on("/pump/on", handlePumpOn);

    server.on(UriBraces("/{}/pump/on"), []() 
        {
            String boxName = server.pathArg(0);

            Box *box = getBoxByName(boxName);

            Serial.println("handleFileRead: " + box->getName());

            server.send(200, "text/plain", "Pump turned on"); 
        }
    );

    server.on("/pump/off", handlePumpOff);
    server.on("/pump/trigger", handlePumpTrigger);
    server.on("/pump/toggle", handlePumpToggle);

    server.on("/light/on", handlePlugOn);
    server.on("/light/off", handlePlugOff);
    server.on("/light/toggle", handlePlugToggle);

    server.on("/reset-wifi", handleResetWifi);

    server.onNotFound([]() {               // If the client requests any URI
        if (!handleFileRead(server.uri())) // send it if it exists
            handleNotFound();
    });

    server.begin();
}

void loop()
{
    server.handleClient();
}

Box *getBoxByName(String name)
{
    for (unsigned int i = 0; i < sizeof Boxes / sizeof Boxes[0]; i++)
    {
        if (Boxes[i].getName() == name)
        {
            return &Boxes[i]; // Return a pointer to the matching object
        }
    }

    return NULL; // Return NULL if no match is found
}

void handleNotFound()
{
    File file = LittleFS.open("/html/error.html", "r");
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return;
    }

    String fileContent;
    while (file.available())
    {
        fileContent += (char)file.read();
    }
    file.close();

    server.send(404, "text/html", fileContent);
}

String getContentType(String filename)
{
    // convert the file extension to the MIME type
    if (filename.endsWith(".html"))
        return "text/html";
    else if (filename.endsWith(".css"))
        return "text/css";
    else if (filename.endsWith(".js"))
        return "application/javascript";
    else if (filename.endsWith(".ico"))
        return "image/x-icon";
    return "text/plain";
}

bool handleFileRead(String path)
{
    // send the right file to the client (if it exists)
    Serial.println("handleFileRead: " + path);
    if (path.endsWith("/"))
        path += "index.html"; // If a folder is requested, send the index file

    String contentType = getContentType(path); // Get the MIME type

    if (LittleFS.exists(path))
    {                                         // If the file exists
        File file = LittleFS.open(path, "r"); // Open it
        server.streamFile(file, contentType); // And send it to the client
        file.close();                         // Then close the file again
        return true;
    }

    Serial.println("\tFile Not Found");

    return false; // If the file doesn't exist, return false
}

void handleDashboard()
{
    File file = LittleFS.open("/html/index.html", "r"); // Open it
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return;
    }

    server.streamFile(file, "text/html", HTTP_GET); // And send it to the client
    file.close();                                   // Then close the file again
}

void handleDevices()
{
    DynamicJsonDocument doc(1024);

    for (unsigned int i = 0; i < sizeof Boxes / sizeof Boxes[0]; i++)
    {
        Box *box = &Boxes[i];
        Relay *pump = box->getPump();
        Relay *light = box->getLight();
        doc["devices"][box->getName()]["pump"]["name"] = pump->getName();
        doc["devices"][box->getName()]["pump"]["state"] = pump->getState();
        doc["devices"][box->getName()]["light"]["name"] = light->getName();
        doc["devices"][box->getName()]["light"]["state"] = light->getState();
    }

    String buf;
    serializeJson(doc, buf);
    server.send(200, F("application/json"), buf);
}

void handlePumpOn()
{
    Box *box = &Boxes[0];
    Relay *pump = box->getPump();

    Serial.println(pump->getName());
    pump->turnON();
    server.send(200, "text/plain", pump->getStateJson());
}

void handlePumpOff()
{
    Box *box = &Boxes[0];
    Serial.println(box->getPump()->getName());
    box->getPump()->turnOFF();
    server.send(200, "text/plain", box->getPump()->getStateJson());
}

void handlePumpToggle()
{
    Box *box = &Boxes[0];
    Serial.println(box->getPump()->getName());
    box->getPump()->toggle();
    server.send(200, "text/plain", box->getPump()->getStateJson());
}

void handlePumpTrigger()
{
    Box *box = &Boxes[0];
    Serial.println(box->getPump()->getName());
    box->getPump()->trigger();
    server.send(200, "text/plain", box->getPump()->getStateJson());
}

void handlePlugOn()
{
    Box *box = &Boxes[0];
    Serial.println(box->getLight()->getName());
    box->getLight()->turnON();
    server.send(200, "text/plain", box->getLight()->getStateJson());
}

void handlePlugOff()
{
    Box *box = &Boxes[0];
    Serial.println(box->getLight()->getName());
    box->getLight()->turnOFF();
    server.send(200, "text/plain", box->getLight()->getStateJson());
}

void handlePlugToggle()
{
    Box *box = &Boxes[0];
    Serial.println(box->getLight()->getName());
    box->getLight()->toggle();
    server.send(200, "text/plain", box->getLight()->getStateJson());
}

void handleResetWifi()
{
    String json;
    StaticJsonDocument<200> doc;
    doc["success"] = "true";
    serializeJson(doc, json);
    server.send(200, "text/plain", json);
    wifiManager.resetSettings();
}