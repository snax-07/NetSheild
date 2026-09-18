#pragma once

#include "tunnel.hpp"
#include "tunnel_state.hpp"

class TunnelManager
{
private:
    Tunnel _tunnel;
    bool _isActiveTunnelManager = false;
public:
    TunnelManager(Tunnel& tunnel);

    bool start();
    void stop();
    bool is_running() const;
    TunnelState get_tunnelState() const;
};