#include "network_manager.hpp"

LinuxNetworkManager::LinuxNetworkManager(){
    _initialized = false;
}


bool LinuxNetworkManager::initialize(){
    if(_initialized)return true;

    _initialized = true;
    return true;
}

void LinuxNetworkManager::shutdown(){
    if(!_initialized) return;
    _initialized = false;
}

bool LinuxNetworkManager::is_initialized() const{
    return _initialized;
}
LinuxNetworkManager::~LinuxNetworkManager(){
    if(!_initialized)return;
    shutdown();
}