#include "network_extension.hpp"

MacOsNetworkExtension::MacOsNetworkExtension(){
    _initialized = false;
}


bool MacOsNetworkExtension::initialize(){
    if(_initialized)return true;

    _initialized = true;
    return true;
}

void MacOsNetworkExtension::shutdown(){
    if(!_initialized) return;
    _initialized = false;
}

bool MacOsNetworkExtension::is_initialized() const{
    return _initialized;
}
MacOsNetworkExtension::~MacOsNetworkExtension(){
    if(!_initialized)return;
    shutdown();
}