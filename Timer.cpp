// Timer.cpp

#include "Timer.h"
#include <Arduino.h>

// Define the default constructor
Timer::Timer()
{
    this->triggerTime = 0;
    this->state = 0;
    this->timeOn = 3000;
    this->timeOff = 10000;
}

Timer::Timer(unsigned char state, long timeOn, long timeOff)
{
    this->triggerTime = 0;
    this->state = state;
    this->timeOn = timeOn;
    this->timeOff = timeOff;
}

void Timer::turnOn()
{
    state = 1;
    triggerTime = millis();
}

void Timer::turnOff()
{
    state = 0;
    triggerTime = 0;
}

unsigned char Timer::getState()
{
    return state;
}

unsigned long Timer::getTriggerTime()
{
    return triggerTime;
}

// bool testIfTimeToToggle()
// {
//     if(state == 1 && millis() - triggerTime > timeOn)
//     {
//         return true;
//     }
// }