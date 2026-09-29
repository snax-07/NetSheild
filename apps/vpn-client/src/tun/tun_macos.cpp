#include "tun_macos.hpp"



#include <string>
#include <arpa/inet.h>
#include <cstdint>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/sys_domain.h>
#include <sys/kern_control.h>
#include <net/if_utun.h>
#include <net/if.h>

TunMacOS::TunMacOS(){
    _open = false;
    _tunFd = -1;
}


bool TunMacOS::open(){
    _tunFd = ::socket(PF_SYSTEM, SOCK_DGRAM, SYSPROTO_CONTROL);
    if (_tunFd < 0) {
        return false;
    };

    struct ctl_info ctlInfo;
    std::memset(&ctlInfo, 0, sizeof(ctlInfo));
    std::strncpy(ctlInfo.ctl_name, UTUN_CONTROL_NAME, sizeof(ctlInfo.ctl_name));
    if (::ioctl(_tunFd, CTLIOCGINFO, &ctlInfo) < 0) {
        ::close(_tunFd);
        return false;
    }
    
        struct sockaddr_ctl sc;
    std::memset(&sc, 0, sizeof(sc));
    sc.sc_len = sizeof(sc);
    sc.sc_family = AF_SYSTEM;
    sc.ss_sysaddr = AF_SYS_CONTROL;
    sc.sc_id = ctlInfo.ctl_id;
    sc.sc_unit = 0; // 0 let the macOS kernel pick the next available unit (utun0, utun1, etc.)

    if (::connect(_tunFd, (struct sockaddr *)&sc, sizeof(sc)) < 0) {
        ::close(_tunFd);
        return false;
    }

    char ifname[IFNAMSIZ];
    std::memset(ifname, 0, sizeof(ifname));
    socklen_t ifname_len = sizeof(ifname);
    if (::getsockopt(_tunFd, SYSPROTO_CONTROL, UTUN_OPT_IFNAME, ifname, &ifname_len) < 0) {
        ::close(_tunFd);
        return false;
    }

    _interface_name = ifname;
    _open = true;

    return true;
}

void TunMacOS::close(){
    if(!_open) return;
    ::close(_tunFd);
    _open = false;
    _tunFd = -1;
    _interface_name = "";
}

std::size_t TunMacOS::read(std::uint8_t* buffer , std::size_t buffer_size){
    if(!_open){
        return 0;
    }

    ssize_t scratch_size = buffer_size + 4;
    auto* scratch_buffer = new std::uint8_t[scratch_size];

    ssize_t nread = ::read(_tunFd, scratch_buffer, scratch_size);
    if (nread <= 4) {
        delete[] scratch_buffer;
        return 0; 
    }

    std::size_t packet_size = nread - 4;
    if(packet_size > buffer_size){
        delete[] scratch_buffer;
        return 0;
    }
        std::memcpy(buffer, scratch_buffer + 4, packet_size);

    delete[] scratch_buffer;
    return packet_size;
}

std::size_t TunMacOS::write(const std::uint8_t* packet_bytes , std::size_t packet_size){
    if(!_open || packet_size == 0 ){
        return 0;
    }

    ssize_t scratch_size = packet_size + 4;
    auto* scratch_buffer = new std::uint8_t[scratch_size];

    std::uint32_t protocol = AF_INET; 
    std::uint8_t ip_version = (packet_bytes[0] >> 4) & 0x0F;
    if (ip_version == 6) {
        protocol = AF_INET6;
    }

    std::uint32_t net_protocol = htonl(protocol);
    std::memcpy(scratch_buffer, &net_protocol, 4);
    std::memcpy(scratch_buffer + 4, packet_bytes, packet_size);
    ssize_t nwrite = ::write(_tunFd, scratch_buffer, scratch_size);
    delete[] scratch_buffer;

    if (nwrite <= 4) {
        return 0;
    }
    return nwrite - 4; 
}


bool TunMacOS::is_open()const{
    return _open;
}

const std::string& TunMacOS::get_interface()const{
    return _interface_name;
}

