#pragma once 

#include <cstddef>
#include <cstdint>

class TunDevice
{
private:
    bool _opened = false;
public:
    TunDevice();
    ~TunDevice();


    bool open();
    void close();
    std::size_t read(
        std::uint8_t* buffer,
        std::size_t buffer_size
    );

    std::size_t write(
        const std::uint8_t* packet_bytes,
        std::size_t packet_size
    );

    bool is_open() const;

};
