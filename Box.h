// Box.h

#ifndef Box_h
#define Box_h

#include <Arduino.h>
#include "Relay.h"

class Box {
private:
    String id;
    String name;
    Relay pump;
    Relay light;

public:
    Box(String boxId, String boxName, uint8_t pumpPinNumber, uint8_t lightPinNumber);
    String getId();
    String getName();
    Relay* getPump();
    Relay* getLight();
};

#endif