#pragma once 

#include <memory>
#include "color.h"

class Image
{
public:
    Color get(int x, int y) const;
    Color median(int x, int y, int radius) const;
    
    static std::shared_ptr<Image> fromBGRA(const uint8_t *data, int width, int height);

    // accessors
    int width() const { return _width; }
    int height() const { return _height; }

protected:
    Image(const uint8_t *data, int width, int height);

private:
    const Color *_data;
    int _width, _height;
};
