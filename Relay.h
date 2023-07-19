// Relay.h
#ifndef Relay_h
#define Relay_h

#include <Arduino.h>
#include <AsyncDelay.h>

class Relay {
  private:
    String name;
    int relayPin;
    unsigned char state;
    unsigned char timerState;
    unsigned char timerTimeOnSec;
    unsigned char timerTimeOffSec;
    AsyncDelay pumpOnDelay;
    AsyncDelay pumpOffDelay;

  public:
    Relay();
    Relay(String name, int relayPin);
    void timerSetup(int timeOnSec, int timeOffSec);
    void timerOn();
    void timerOff();
    void turnON();
    void turnOFF();
    void toggle();
    void trigger();
    int getPin();
    int getState();
    String getName();
    String getStateJson();
    AsyncDelay * getPumpOnDelay();
    AsyncDelay * getPumpOffDelay();
    bool getTimerState();
    unsigned char getTimerTimeOnSec();
    unsigned char getTimerTimeOffSec();
};


#endif
