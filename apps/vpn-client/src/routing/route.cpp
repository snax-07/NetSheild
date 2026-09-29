#include "route.hpp"

#include <string>
#include <cstdint>
#include <cstddef>

Route::Route(const std::string& destination, std::uint8_t prefix_length , const std::string& gateway,const std::string& interface_name) :  
        _destination(destination) , _prefixed_length(prefix_length) , _gateway(gateway) ,_interfaceName(interface_name) {
};

const std::string& Route::get_destination() const{
    return _destination;
}


std::uint8_t Route::get_prefix_length() const{
    return _prefixed_length;
};
const std::string& Route::get_gateway() const{
    return _gateway;
};
const std::string& Route::get_interface_name() const{
    return _interfaceName;
};