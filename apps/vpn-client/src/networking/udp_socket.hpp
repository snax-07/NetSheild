#pragma once

#include "udp_endpoint.hpp"


#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <string>
#include <netinet/in.h>

class UdpSocket {
private:
    int _sockfd{-1};
    sockaddr_in _server_addr{};
    bool is_bounded = false;

public:


    UdpSocket();//constructor
    ~UdpSocket();//destructor

    // THIS CODE OF SNIPPET MAKE SURE THA NONE OF OBJECT IS COPYABLE AND 
    // ENSURE THAT CONNECTION IS VALID AND CAN'T GET COPY
    UdpSocket(const UdpSocket&) = delete;
    UdpSocket& operator=(const UdpSocket&) = delete;

    //===============OWNERSHIP TRANSFER===========//
    UdpSocket(UdpSocket&& other)
        : _sockfd(other._sockfd)
    {
        other._sockfd = -1;
    }

    UdpSocket& operator=(UdpSocket&& other);
    

    bool open();

    bool _bind(
        const UdpEndpoint& local_endpoint
    );

    std::size_t send(
        const std::uint8_t* message_bytes,
        std::size_t message_size,
        UdpEndpoint& destination
    );

    std::size_t receive(
        std::uint8_t* buffer,
        std::size_t buffer_size,
        UdpEndpoint& sender
    );

    void _close();

    bool is_socket_open();
};