#include "tun_linux.hpp"

#include <cstring>
#include <fcntl.h>      
#include <unistd.h>     
#include <sys/ioctl.h>  
#include <net/if.h>    

#ifdef __linux__
#include <linux/if_tun.h> 
#endif



TunLinux::TunLinux(){
    _open = false;
    _tunFd = -1;
}


bool TunLinux::open(){

    _tunFd = ::open("/dev/net/tun" , O_RDWR);
    if(_tunFd < 0){
        return false;
    }


    struct ifreq ifr{};
     std::memset(&ifr, 0, sizeof(ifr));
     ifr.ifr_ifru.ifru_flags = IFF_TUN | IFF_NO_PI;
    std::strncpy(ifr.ifr_name, "nstun0", IFNAMSIZ);
    _interface_name = ifr.ifr_name;


    if (ioctl(_tunFd, TUNSETIFF, (void*)&ifr) < 0) {
        ::close(_tunFd);
        return false;
    }

    _open = true;

    return true;
}

void TunLinux::close(){
    if(!_open) return;
    ::close(_tunFd);
    _open = false;
    _tunFd = -1;
    _interface_name = "";
}

std::size_t TunLinux::read(std::uint8_t* buffer , std::size_t buffer_size){
    if(!_open){
        return 0;
    }
    ssize_t nread = ::read(_tunFd , buffer , buffer_size);
    if(nread < 0){
        return 0;
    }
    
    return nread;
}

std::size_t TunLinux::write(const std::uint8_t* packet_bytes , std::size_t packet_size){
    if(!_open){
        return 0;
    }
    ssize_t nwrite = ::write(_tunFd , packet_bytes , packet_size);
    if(nwrite < 0){
        return 0;
    }
    return nwrite; 
}

bool TunLinux::is_open()const{
    return _open;
}

const std::string& TunLinux::get_interface()const{
    return _interface_name;
}

