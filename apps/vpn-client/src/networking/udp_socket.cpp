#include "udp_socket.hpp"

#include <arpa/inet.h>
#include <cerrno>
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define MAXLINE_BUFFER 65535

UdpSocket::UdpSocket() = default;
UdpSocket::~UdpSocket(){
    _close();
}

UdpSocket& UdpSocket::operator=(UdpSocket&& other){
    if(this != &other){
        this->_close();
        this->_sockfd = other._sockfd;
        other._sockfd = -1;
        return *this;
    }

    return *this;
}

bool UdpSocket::open() {

    if(is_socket_open()) return true;
    _sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (_sockfd < 0) {
        perror("SOCKET CREATION FAILED");
        return false;
    }

    return true;
}

bool UdpSocket::_bind(
    const UdpEndpoint& local_endpoint
) {

    if(!is_socket_open()) return false;
    if(is_bounded) return true;
    std::memset(&_server_addr, 0, sizeof(_server_addr));

    _server_addr.sin_family = AF_INET;
    _server_addr.sin_port = htons(local_endpoint.getPort());
    inet_pton(AF_INET , (const char *)&local_endpoint.getAddress() , &_server_addr.sin_addr);

    if (bind(
            _sockfd,
            reinterpret_cast<const sockaddr*>(&_server_addr),
            sizeof(_server_addr)
        ) < 0) {

        perror("SOCKET BIND FAILED");
        return false;
    }
    is_bounded = true;
    return true;
}

std::size_t UdpSocket::send(
        const std::uint8_t* message_bytes,
        std::size_t message_size,
    UdpEndpoint& destination
) {

    if(!is_socket_open() || !is_bounded) return 0;
    sockaddr_in destination_addr{};
    
    destination_addr.sin_family = AF_INET;
    destination_addr.sin_port = htons(destination.getPort());
    
    if (inet_pton(
        AF_INET,
        destination.getAddress().c_str(),
        &destination_addr.sin_addr
    ) != 1) {
        std::cerr << "INVALID DESTINATION ADDRESS\n";
        return 0;
    }
    
    const ssize_t msg_bytes = sendto(
        _sockfd,
        message_bytes,
        message_size,
        0,
        reinterpret_cast<const sockaddr*>(&destination_addr),
        sizeof(destination_addr)
    );

    if (msg_bytes <= 0) {
        perror("MESSAGE SEND FAILED");
        return 0;
    }

    std::cout << "message bytes from udp cosket " << msg_bytes;

    return static_cast<std::size_t>(msg_bytes);
}

std::size_t UdpSocket::receive(
    std::uint8_t* buffer,
    std::size_t buffer_size,
    UdpEndpoint& sender
) {

    //safety check
    if(!is_socket_open() && !is_bounded) return false;
    if(!buffer || buffer_size == 0) return 0;
    sockaddr_in sender_address{};
    socklen_t address_length = sizeof(sender_address);

    const ssize_t message_bytes = recvfrom(
        _sockfd,
        buffer,
        buffer_size,
        0,
        reinterpret_cast<sockaddr*>(&sender_address),
        &address_length
    );

    if (!message_bytes) {
        perror("MESSAGE RECEIVE FAILED");
        return 0;
    }

    char sender_ip[INET_ADDRSTRLEN]{};

    if (inet_ntop(
            AF_INET,
            &sender_address.sin_addr,
            sender_ip,
            sizeof(sender_ip)
        ) == nullptr) {
        perror("SENDER ADDRESS CONVERSION FAILED");
        return 0;
    }

    sender = UdpEndpoint(
        sender_ip,
        ntohs(sender_address.sin_port)
    );

    return static_cast<std::size_t>(message_bytes);
}

void UdpSocket::_close() {
    if(!is_socket_open()) return;
    if (_sockfd >= 0) {
        close(_sockfd);
        _sockfd = -1;
        is_bounded = false;
    }
}


bool UdpSocket::is_socket_open(){
    return _sockfd != -1;
}