#pragma once

#include "source.h"

class LolSource : public Source
{
public: 
    void run(Controller *controller);

private:
    Controller *_controller;
};