#include "tunnel_manager.hpp"




TunnelManager::TunnelManager(Tunnel& tunnel) : _tunnel(tunnel){
}


bool TunnelManager::start(){
    if(!_tunnel.start())return false;
    _isActiveTunnelManager = true;
    return true;
}

void TunnelManager::stop(){
    if(!_isActiveTunnelManager)return;
    _tunnel.stop();
    _isActiveTunnelManager = false;
}

bool TunnelManager::is_running() const{
    return _isActiveTunnelManager;
}

TunnelState TunnelManager::get_tunnelState() const{
    return _tunnel.get_state();
}