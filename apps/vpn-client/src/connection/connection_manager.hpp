#pragma once

#include "../networking/udp_endpoint.hpp"
#include "udp_connection.hpp"
#include <cstdint>
#include <cstddef>

class connection_manager
{
private:
    UdpConnection& _udpConnection;
    bool isUdpSocketConnected = false;
    bool isManageActive = false;
public:
    connection_manager(UdpConnection& udpConnection);
    ~connection_manager();

    //this is reponsible for starting the udp connection
    bool start(UdpEndpoint& endpoint);

    std::size_t send(std::uint8_t* message_bytes , std::size_t message_size);

    std::size_t receive(
                std::uint8_t* buffer,
        std::size_t buffer_size
    );

    void stop();

     bool is_udp_running() const&;

};
