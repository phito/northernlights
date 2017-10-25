#pragma once

#include <stdint.h>
#include "color.h"

class Controller
{
public:
    virtual void init() = 0;
    virtual void set(Color color) = 0;
    virtual void set(uint8_t led, Color color) = 0;
    virtual void set(Color colors[], uint8_t length) = 0;
    virtual void reset() = 0;
    virtual void dispose() = 0;
};