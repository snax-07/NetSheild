

#include "connection_manager.hpp"
#include "../networking/udp_endpoint.hpp"
#include "udp_connection.hpp"




connection_manager::connection_manager(UdpConnection& udpConnection)
    : _udpConnection(udpConnection)
{
}
bool connection_manager::start(UdpEndpoint& endpoint){
    if(!_udpConnection.connect(endpoint)){
        isManageActive = false;
        return false;
    }
    isManageActive = true;
    return true;
}

std::size_t connection_manager::send(std::uint8_t* message_bytes , std::size_t message_size){
    
    if(!isManageActive)return 0;
    
    return _udpConnection.send(message_bytes , message_size);
}

std::size_t connection_manager::receive(std::uint8_t* buffer, std::size_t buffer_size){
            if(!isManageActive)return 0;
    return _udpConnection.receive(buffer , buffer_size);
}

void connection_manager::stop(){
    if(!isManageActive || !_udpConnection.is_connected()) return;
    _udpConnection.disconnect();
    isManageActive = false;
}

bool connection_manager::is_udp_running() const&{
    return isManageActive;
}