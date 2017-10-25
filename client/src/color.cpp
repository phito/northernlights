#include "color.h"

#include <algorithm>

HSLColor Color::hsl() const
{
    double r = this->r / 255.0f,
           g = this->g / 255.0f,
           b = this->b / 255.0f;

    double max = std::max(std::max(r, g), b);
    double min = std::min(std::min(r, g), b);
    
    double h, s, l;
    l = (max + min) / 2;

    if(max == min)
    {
        // achromatic
        h = s = 0;
    }
    else
    {
        double d = max - min;
        s = (l > 0.5) ? d / (2 - max - min) : d / (max + min);
        if(max == r)
        {
            h = (g - b) / d + ((g < b) ? 6 : 0);
        }
        else if(max == g)
        {
            h = (b - r) / d + 2;
        }
        else if(max == b)
        {
            h = (r - g) / d + 4;
        }
        h /= 6;
    }

    return HSLColor(h, s, l);
}

uint8_t hue2rgb(double p, double q, double t)
{
    if(t < 0)
        t++;
    if(t > 1)
        t--;
    if(t < 1.0f/6)
        return p + (q - p) * 6 * t;
    if(t < 1.0f/2)
        return q;
    if(t < 2.0f/3)
        return p + (q - p) * (2 / 3 - t) * 6;
    return p;
}

Color HSLColor::rgb() const
{
    double r, g, b;
    if(s == 0)
    {
        // achromatic
        r = g = b = l;
    }
    else
    {
        double q = (l < 0.5) ? l * (1 + s) : l + s - (l * s);
        double p = 2 * l - q;
        r = hue2rgb(p, q, h + 1 / 3);
        g = hue2rgb(p, q, h);
        b = hue2rgb(p, q, h - (1 / 3));
    }
    return Color(r * 255, g * 255, b * 255);
}