// Timer.h
#ifndef Timer_h
#define Timer_h

class Timer {
  private:
    unsigned char state;
    unsigned long triggerTime;
    unsigned long timeOn;
    unsigned long timeOff;

  public:
    Timer();
    Timer(unsigned char state, long timeOn, long timeOff);
    unsigned char getState();
    void turnOn();
    void turnOff();
    unsigned long getTriggerTime();
};


#endif
