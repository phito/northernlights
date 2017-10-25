#include "win32/udpcontroller.h"

#if defined(_WIN32)

#pragma comment(lib,"ws2_32.lib") 

void UdpController::init()
{
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        throw std::runtime_error("could not initialise winsock");
    }
    if((_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
    {
        throw std::runtime_error("could not create socket");
    }

    _serveraddr.sin_family = AF_INET;
    _serveraddr.sin_addr.s_addr = inet_addr(_hostname.c_str());
    _serveraddr.sin_port = htons(_port);
}

void UdpController::dispose()
{
    closesocket(_sockfd);
    WSACleanup();
}

void UdpController::set(Color color)
{
	char data[] = {
        1,
        color.r,
        color.g,
        color.b
    };
    send(data, sizeof(data));
}

void UdpController::set(uint8_t led, Color color)
{
	char data[] = {
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
	char *data = new char[length*3 + 1];
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
	char data[] {
        4
    };
    send(data, sizeof(data));
}

void UdpController::send(const char *data, size_t length)
{
    int n;
    int serverlen;

    /* send the message to the server */
    serverlen = sizeof(_serveraddr);
    n = sendto(_sockfd, (const char*)data, length, 0, (struct sockaddr*)&_serveraddr, serverlen);
    if (n == SOCKET_ERROR)
    {
        throw std::runtime_error("error while sending data");
    }
}

#endif