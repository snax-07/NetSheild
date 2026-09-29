#pragma once
#include <cstdint>
#include <cstddef>
#include <string>

class Route{
    private:
        std::string _destination;
        std::uint8_t _prefixed_length;
        std::string _gateway;
        std::string _interfaceName;
    
    public:
        Route(const std::string& destination, std::uint8_t prefix_length , const std::string& gateway,const std::string& interface_name);


        const std::string& get_destination() const;
        std::uint8_t get_prefix_length() const;
        const std::string& get_gateway() const;
        const std::string& get_interface_name() const;

};