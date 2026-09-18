
#pragma once


#include "../networking/udp_socket.hpp"
#include "../networking/udp_endpoint.hpp"

#include <cstdint>
#include <cstddef>

class UdpConnection{
private:
bool isConnected = false;
UdpSocket _socket;
UdpEndpoint _udpEndpoint;



public:
    UdpConnection();

    bool connect(const UdpEndpoint& endpoint);
    std::size_t send(
       const std::uint8_t* message_bytes,
        std::size_t message_size
    );
    std::size_t receive(
        std::uint8_t* buffer,
        std::size_t buffer_size
    );
    void disconnect();
     bool is_connected() const;
};