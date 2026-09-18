#include "tunnel.hpp"

Tunnel::Tunnel(UdpConnection& udpConnection)
    : _tunnleState(TunnelState::_STOPPED) , _udpConnection(udpConnection)
      
{}

bool Tunnel::start(){

    if(_tunnleState == TunnelState::_STARTING || _tunnleState == TunnelState::_RUNNING) return true;
    //start the tunnnel 
    _tunnleState = TunnelState::_STARTING;
    //after all successful operation change the state
    _tunnleState = TunnelState::_RUNNING;


    return true;
};

void Tunnel::stop(){
    if(_tunnleState == TunnelState::_STOPPED || _tunnleState == TunnelState::_STOPPING)return;
    //stop all tunnel and free all memory and also free the port and all network resources
    _tunnleState = TunnelState::_STOPPING;

    _udpConnection.disconnect();
    //after all clearing things done then complty off the client
    _tunnleState = TunnelState::_STOPPED;
};

bool Tunnel::is_running() const{
    return _tunnleState == TunnelState::_RUNNING;
};

TunnelState Tunnel::get_state() const{
    return _tunnleState;
}