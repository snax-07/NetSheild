#include "client_application.hpp"
#include "../connection/connection_manager.hpp"
#include "../networking/udp_endpoint.hpp"
#include "../connection/udp_connection.hpp"


#include <string>
#include <iostream>
#include <cstdint>
#include <cstddef>



ClientApplication::ClientApplication()
{
}


void ClientApplication::run(){
    UdpConnection udpConnection;
connection_manager* mng = new connection_manager(udpConnection);
    UdpEndpoint* end = new UdpEndpoint("127.0.0.1" , 8080);
    mng->start(*end) ? 
    std::cout << "started" : std::cout << "Not Started";
    mng->is_udp_running();

std::uint8_t message_bytes[] = {
    0x4E, 0x65, 0x74, 0x53,
    0x68, 0x69, 0x65, 0x6C,
    0x64
};

std::string demoMessage = "hello";


std::size_t message_size = sizeof(message_bytes);


std::cout << mng->send(message_bytes , message_size);
}

void ClientApplication::stop(){
    std::cout << "stopped";
}


