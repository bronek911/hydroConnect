// Relay.cpp

#include "Relay.h"
#include <ArduinoJson.h>
#include <AsyncDelay.h>

// Define the default constructor
Relay::Relay()
{
    // Initialize member variables to default values
    name = "";
    relayPin = 0;
}

Relay::Relay(String name, int pin)
{
    this->name = name;
    relayPin = pin;
    state = LOW;
    pinMode(relayPin, OUTPUT);

    this->timer = Timer(0, 3, 10);
}

Timer* Relay::getTimer()
{
    return &timer;
}

void Relay::turnON()
{
    state = HIGH;
    digitalWrite(relayPin, state);
}

void Relay::turnOFF()
{
    state = LOW;
    digitalWrite(relayPin, state);
}

void Relay::toggle()
{
    if (state == LOW){
        turnON();
    }
    else
    {
        turnOFF();
    }
}

void Relay::trigger()
{
    turnON();
    delay(500);
    turnOFF();
}

int Relay::getState()
{
    return state;
}

String Relay::getName()
{
    return name;
}

int Relay::getPin()
{
    return relayPin;
}

void Relay::timerSetup(int timeOnSec, int timeOffSec)
{
    timerTimeOnSec = timeOnSec;
    timerTimeOffSec = timeOffSec;
}

String Relay::getStateJson()
{
    DynamicJsonDocument doc(200);
    doc["name"] = name;
    doc["state"] = state;
    String json;
    serializeJson(doc, json);
    return json;
}

bool Relay::getTimerState() {
  return timerState;
}

unsigned char Relay::getTimerTimeOnSec() {
  return timerTimeOnSec;
}

unsigned char Relay::getTimerTimeOffSec() {
  return timerTimeOffSec;
}