#pragma once

#include <stdint.h>

struct HSLColor;

struct Color
{
public:
    Color(){}
    Color(uint8_t r, uint8_t g, uint8_t b)
        : b(b), g(g), r(r), a(255) {}

    HSLColor hsl() const;

    uint8_t b, g, r, a;
};

struct HSLColor
{
public:
    HSLColor() {}
    HSLColor(double h, double s, double l)
        : h(h), s(s), l(l) {}

    Color rgb() const;

    double h, s, l;
};