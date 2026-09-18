#pragma once


#include <string>

#include <cstdint>
#include <cstddef>


class UdpEndpoint {
private:
    std::string address;
    std::uint16_t port;

public:
    UdpEndpoint() : address(""), port(0) {}

    UdpEndpoint(const std::string& address, std::uint16_t port)
        : address(address), port(port) {}

    const std::string& getAddress() const {
        return address;
    }

    std::uint16_t getPort() const {
        return port;
    }
};