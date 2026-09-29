#pragma once

#include <vector>
#include <string>

class DNSConfig{
private:
    std::vector<std::string> _dns_servers;
    bool _isEnabled;
public: 
    DNSConfig();
    void add_server(const std::string& server);
    bool remove_server(const std::string& server);
    const std::vector<std::string>& get_servers() const;
    void set_enabled(bool enabled);
    bool is_enabled() const;
};