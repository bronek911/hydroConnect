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

    timerState = 0;
    timerTimeOnSec = 3;
    timerTimeOffSec = 10;
}

Relay::Relay(String name, int pin)
{
    this->name = name;
    relayPin = pin;
    state = LOW;
    pinMode(relayPin, OUTPUT);

    timerState = 0;
    timerTimeOnSec = 3;
    timerTimeOffSec = 10;

    pumpOnDelay.start(timerTimeOnSec * 1000, AsyncDelay::MILLIS);
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

void Relay::timerOn()
{
    timerState = 1;
}

void Relay::timerOff()
{
    timerState = 0;
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

AsyncDelay* Relay::getPumpOnDelay() {
  return &pumpOnDelay;
}

AsyncDelay* Relay::getPumpOffDelay() {
  return &pumpOffDelay;
}

unsigned char Relay::getTimerTimeOnSec() {
  return timerTimeOnSec;
}

unsigned char Relay::getTimerTimeOffSec() {
  return timerTimeOffSec;
}