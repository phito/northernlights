#include "unix/udpcontroller.h"

#if defined(_WIN32)

#pragma comment(lib,"ws2_32.lib") 

void UdpController::init()
{
}

void UdpController::dispose()
{
}

void UdpController::set(Color color)
{
    uint8_t data[] = {
        1,
        color.r,
        color.g,
        color.b
    };
    send(data, sizeof(data));
}

void UdpController::set(uint8_t led, Color color)
{
    uint8_t data[] = {
        2,
        led,
        color.r,
        color.g,
        color.b
    };
    send(data, sizeof(data));
}

void UdpController::set(Color colors[], uint8_t length)
{
    uint8_t *data = new uint8_t[length*3 + 1];
    data[0] = 3;
    for(int i=0; i<length; i++)
    {
        int index = i*3 + 1;
        data[index] = colors[i].r;
        data[index+1] = colors[i].g;
        data[index+2] = colors[i].b;
    }
    send(data, length*3 + 1);
    delete[] data;
}

void UdpController::reset()
{
    uint8_t data[] {
        4
    };
    send(data, sizeof(data));
}

void UdpController::send(const uint8_t *data, size_t length)
{
}

#endif