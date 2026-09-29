#include "dns_config.hpp"
#include "helper/IpHelper.hpp"


#include <algorithm>
#include <string>
#include <vector>

DNSConfig::DNSConfig(){
    _dns_servers = {};
    _isEnabled = false;
}



void DNSConfig::add_server(const std::string& server){
    if(server.empty())return;
    
    bool ipv4 = IpHelper::isIPv4(server);
    bool ipv6 = IpHelper::isIPv6(server);

    if(!ipv4 && !ipv6){
        return;
    }
    bool _exits = std::find(_dns_servers.begin() , _dns_servers.end() , server) != _dns_servers.end();
    if(_exits)return;
    _dns_servers.push_back(server);
}

bool DNSConfig::remove_server(const std::string& server){
    if(server.empty())return true;
    
    bool ipv4 = IpHelper::isIPv4(server);
    bool ipv6 = IpHelper::isIPv6(server);
    
    if(!ipv4 && !ipv6){
        return false;
    }
    auto it = std::find(_dns_servers.begin() , _dns_servers.end() , server);

    if(it != _dns_servers.end()){
        _dns_servers.erase(it);
        return true;
    }
    return true;
}

const std::vector<std::string>& DNSConfig::get_servers() const{
    return _dns_servers;
}

void DNSConfig::set_enabled(bool enabled){
    _isEnabled = enabled;
}

bool DNSConfig::is_enabled() const{
    return _isEnabled;
}
