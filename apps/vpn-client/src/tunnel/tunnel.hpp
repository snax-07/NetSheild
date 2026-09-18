#pragma once

#include "tunnel_state.hpp"
#include "../connection/udp_connection.hpp"

class Tunnel
{
private:
    TunnelState _tunnleState;
    UdpConnection& _udpConnection;
public:
    Tunnel(UdpConnection& udpConnection);//intialize the tunnel state as stopped 
    ~Tunnel();




    //this will start the tunnel
    bool start();
    void stop();
    bool is_running() const;
    TunnelState get_state() const;
};
