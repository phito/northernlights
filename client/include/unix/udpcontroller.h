#pragma once

#include <string>
#include <netinet/in.h>
#include "controller.h"

class UdpController : public Controller
{
public:
    void init();
    void dispose();

    void set(Color color);
    void set(uint8_t led, Color color);
    void set(Color colors[], uint8_t length);
    void reset();

    // accessors
    const std::string& hostname() const { return _hostname; }
    void setHostname(const std::string &value) { _hostname = value; }

    int port() const { return _port; }
    void setPort(int value) { _port = value; }

private:
    std::string _hostname;
    int _port; 

    // udp related
    int _sockfd;
    struct sockaddr_in _serveraddr;
    void send(const uint8_t *data, size_t length);
};