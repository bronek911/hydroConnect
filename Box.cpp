// Box.cpp

#include "Box.h"
#include "Relay.h"
#include <ArduinoJson.h>

Box::Box(String id, String name, uint8_t pumpPinNumber, uint8_t lightPinNumber)
{
    this->id = id;
    this->name = name;
    this->pump = Relay("pump", pumpPinNumber);
    this->light = Relay("light", lightPinNumber);
}

String Box::getId()
{
    return id;
}

String Box::getName()
{
    return name;
}

Relay* Box::getPump()
{
    return &pump;
}

Relay* Box::getLight()
{
    return &light;
}