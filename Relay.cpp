// Relay.cpp

#include "Relay.h"
#include <ArduinoJson.h>

// Define the default constructor
Relay::Relay() {
    // Initialize member variables to default values
    name = "";
    relayPin = 0;
}

Relay::Relay(String name, int pin) {
  this->name = name;
  relayPin = pin;
  state = LOW;
  pinMode(relayPin, OUTPUT);
}

void Relay::turnON() {
  state = HIGH;
  digitalWrite(relayPin, state);
}

void Relay::turnOFF() {
  state = LOW;
  digitalWrite(relayPin, state);
}

void Relay::toggle() {
    if( state == LOW ) {
        turnON();
    } else {
        turnOFF();
    }
}

void Relay::trigger() {
    turnON();
    delay(500);
    turnOFF();
}

int Relay::getState() {
  return state;
}

String Relay::getName() {
  return name;
}

int Relay::getPin() {
  return relayPin;
}

String Relay::getStateJson(){
    DynamicJsonDocument doc(200);  
    doc["name"] = name;
    doc["state"] = state;
    String json;
    serializeJson(doc, json);
    return json;
}
