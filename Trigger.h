// Trigger.h
#ifndef Trigger_h
#define Trigger_h

#include <Arduino.h>

class Trigger {
  private:
    String name;
    int relayPin;
    unsigned char state;

  public:
    Relay(String name, int relayPin);
    void run();
    int getPin();
    int getState();
    String getName();
};


#endif
