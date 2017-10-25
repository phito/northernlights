#pragma once

#include <ScreenCapture.h>
#include "image.h"
#include "source.h"

class ScreenSource : public Source
{
public: 
    void run(Controller *controller);

    void enable() { _active = true; }
    void disable() { _active = false; }
    bool active() const { return _active; }

private:
    Controller *_controller;
    bool _active;
    std::shared_ptr<SL::Screen_Capture::IScreenCaptureManager> _framgrabber;

    void processFrame(std::shared_ptr<Image> image);
};