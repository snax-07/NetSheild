#include <iostream>
#include "udp_connection.hpp"
#include "../networking/udp_socket.hpp"
#include "../networking/udp_endpoint.hpp"


UdpConnection::UdpConnection() = default;
bool UdpConnection::connect(const UdpEndpoint& endpoint){
    if (!_socket.open())
    {
        //print the error in console and exit program
        return false;
    }

    //This snippet iis used for bind that ip to local machine arp mechanism  for testing purpose
    UdpEndpoint* endpnt = new UdpEndpoint("127.0.0.1" , 8000);
    if(!_socket._bind(*endpnt)){
        return false;
    }
    
    
    _udpEndpoint = endpoint;
    isConnected = true;
    return true;
}

std::size_t UdpConnection::send(const std::uint8_t* message_bytes, std::size_t message_size){

  return  _socket.send(message_bytes , message_size , _udpEndpoint);
}

std::size_t UdpConnection::receive(std::uint8_t* buffer, std::size_t buffer_size){
    return _socket.receive(buffer , buffer_size , _udpEndpoint);
}

void UdpConnection::disconnect(){
    _socket._close();
    isConnected = false;
}
bool UdpConnection::is_connected() const {
    return isConnected;
}