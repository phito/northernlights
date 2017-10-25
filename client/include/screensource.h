#pragma once

#include <ScreenCapture.h>
#include "image.h"
#include "source.h"

class ScreenSource : public Source
{
public: 
    void run(Controller *controller);

private:
    Controller *_controller;
    std::shared_ptr<SL::Screen_Capture::IScreenCaptureManager> _framgrabber;

    void processFrame(std::shared_ptr<Image> image);
};