#include "udpcontroller.h"
#include "screensource.h"

#include <unistd.h>

int main()
{
    ScreenSource source;
    UdpController controller;
    controller.setHostname("192.168.0.98");
    controller.setPort(1612);
    controller.init();

    source.run(&controller);
    getchar();
    controller.reset();

    return 0;
}