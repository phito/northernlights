#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

class Controller : public Adafruit_NeoPixel 
{
public:
    Controller(uint16_t n, uint8_t p, neoPixelType t) : Adafruit_NeoPixel(n, p, t)  {}
    void init();
    void service();

    void setColor(int8_t r, int8_t g, int8_t b);
    void setColor(int16_t led, int8_t r, int8_t g, int8_t b);
};

#endif