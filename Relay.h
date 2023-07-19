// Relay.h
#ifndef Relay_h
#define Relay_h

#include <Arduino.h>
#include "Timer.h"

class Relay {
  private:
    String name;
    int relayPin;
    unsigned char state;
    unsigned char timerState;
    unsigned char timerTimeOnSec;
    unsigned char timerTimeOffSec;
    Timer timer;

  public:
    Relay();
    Relay(String name, int relayPin);
    void timerSetup(int timeOnSec, int timeOffSec);
    void turnON();
    void turnOFF();
    void toggle();
    void trigger();
    int getPin();
    int getState();
    String getName();
    String getStateJson();
    bool getTimerState();
    unsigned char getTimerTimeOnSec();
    unsigned char getTimerTimeOffSec();
    Timer* getTimer();
};


#endif
