#include "screensource.h"

#include <random>
#include "image.h"

void ScreenSource::run(Controller *controller)
{    
    _controller = controller;
    _framgrabber =
    SL::Screen_Capture::CreateCaptureConfiguration([]() {
        return SL::Screen_Capture::GetMonitors();
    })->onNewFrame([&](const SL::Screen_Capture::Image &img, const SL::Screen_Capture::Monitor &monitor) {
        auto image = Image::fromBGRA(img.Data, img.Bounds.right, img.Bounds.bottom);
        this->processFrame(image);
    })->start_capturing();

    _framgrabber->setFrameChangeInterval(std::chrono::milliseconds(50));
}

#define LEFT_LED 10
#define TOP_LED 20
#define RIGHT_LED 10 
#define BOTTOM_LED 20

void ScreenSource::processFrame(std::shared_ptr<Image> image)
{   
    Color colors[65];
    int i = 0;

    int left =   image->height() / LEFT_LED;
    int top =    image->width()   / TOP_LED;
    int right =  image->height() / RIGHT_LED;
    int bottom = image->width()  / BOTTOM_LED;
    
    for(int y=image->height(); y >= 0; y -= left)
    {
        colors[i++] = image->median(0, y, left);
    }
    
    for(int x=0; x < image->width(); x += top)
    {
        colors[i++] = image->median(x, 0, top);
    }

    for(int y=0; y < image->height(); y += right)
    {
        colors[i++] = image->median(image->width() - 1, y, right);
    }
    
    for(int x=image->width(); x >= 0; x -= bottom)
    {
        colors[i++] = image->median(x, image->height() - 1, bottom);
    }
    
    _controller->set(colors, 61);
}