// Relay.h
#ifndef Relay_h
#define Relay_h

#include <Arduino.h>

class Relay {
  private:
    String name;
    int relayPin;
    unsigned char state;

  public:
    Relay();
    Relay(String name, int relayPin);
    void turnON();
    void turnOFF();
    void toggle();
    void trigger();
    int getPin();
    int getState();
    String getName();
    String getStateJson();
};


#endif
