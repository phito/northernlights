#pragma once

#include "controller.h"

class Source
{
public:
    virtual void run(Controller *controller) = 0;
};