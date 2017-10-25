#include "controller.h"

void Controller::init()
{
    Adafruit_NeoPixel::begin();
    Adafruit_NeoPixel::show();
}

void Controller::service()
{
    Adafruit_NeoPixel::setBrightness(100);
    Adafruit_NeoPixel::show();
}

void Controller::setColor(int8_t r, int8_t g, int8_t b)
{
    for(int i=0; i < Adafruit_NeoPixel::numPixels(); i++)
    {
        Adafruit_NeoPixel::setPixelColor(i, r, g, b);
    }
}

void Controller::setColor(int16_t led, int8_t r, int8_t g, int8_t b)
{
    Adafruit_NeoPixel::setPixelColor(led, r, g, b);
}