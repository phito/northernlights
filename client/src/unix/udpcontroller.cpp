#include "unix/udpcontroller.h"

#if defined(__unix__)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h> 
#include <stdexcept>

void UdpController::init()
{
    struct hostent *server;
    _sockfd = socket(AF_INET, SOCK_DGRAM, 0);

     if (_sockfd < 0)
     {
         throw std::runtime_error("cannot open socket");
     }

    // gethostbyname: get the server's DNS entry
    server = gethostbyname(_hostname.c_str());
    if (server == nullptr)
    {
        throw std::runtime_error("no such host");
    }

    // build the server's Internet address
    bzero((char *) &_serveraddr, sizeof(_serveraddr));
    _serveraddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&_serveraddr.sin_addr.s_addr, server->h_length);
    _serveraddr.sin_port = htons(_port);
}

void UdpController::dispose()
{
    close(_sockfd);
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
    int n;
    int serverlen;

    /* send the message to the server */
    serverlen = sizeof(_serveraddr);
    n = sendto(_sockfd, data, length, 0, (struct sockaddr*)&_serveraddr, serverlen);
    if (n < 0)
    {
        throw std::runtime_error("error while sending data");
    }
}

#endif