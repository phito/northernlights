#include "image.h"

#include <stdexcept>
#include <iostream>

using namespace std;

Image::Image(const uint8_t *data, int width, int height)
    : _width(width), _height(height)
{
    _data = (const Color*)data;
}

Color Image::get(int x, int y) const
{
    return _data[y*_width + x];
}

Color Image::median(int x, int y, int radius) const
{
    uint64_t r = 0, g = 0, b = 0;
    int count = 0;
    for(int i=-radius; i <= radius; i++)
    for(int j=-radius; j <= radius; j++)
    {
        int _x = x + i;
        int _y = y + j;
        if(_x >= 0 && _y >= 0 && _x < _width && _y < _height)
        {
            Color color = get(_x, _y);
            r += color.r;
            g += color.g;
            b += color.b;            
            count++;
        }
    }
    return Color(r/count, g/count, b/count);
}

std::shared_ptr<Image> Image::fromBGRA(const uint8_t *data, int width, int height)
{
    std::shared_ptr<Image> image(new Image(data, width, height));
    return image;
}