#include "tun_device.hpp"

#include <cstdint>
#include <cstddef>

TunDevice::TunDevice(){
    _opened = false;
}

bool TunDevice::open(){
    if(_opened) return true;

    _opened = true;
    return true;
}

void TunDevice::close(){
    if(!_opened) return;
    _opened = false;
}

std::size_t TunDevice::read(std::uint8_t* buffer , std::size_t buffer_size){
    if(!_opened) return 0;
    //reading mechanism
    return 0;
}

std::size_t TunDevice::write(const std::uint8_t* packet_bytes , std::size_t packet_size){
    if(!_opened) return 0;
    //reading mechanism
    return 0;
}

bool TunDevice::is_open() const{
    return _opened;
}



TunDevice::~TunDevice(){
    close();
}