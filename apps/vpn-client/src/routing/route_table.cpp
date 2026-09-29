#include "route_table.hpp"
#include "helper/IpHelper.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <arpa/inet.h>
#include <cstdint>
#include <cstddef>

uint32_t ipv4ToUint32(const std::string& ip)
{
    std::stringstream ss(ip);
    std::string part;

    uint32_t result = 0;

    for (int i = 0; i < 4; ++i) {
        std::getline(ss, part, '.');

        uint32_t octet = std::stoi(part);

        result = (result << 8) | octet;
    }

    return result;
}

struct IPv6Mask {
    std::uint64_t high;
    std::uint64_t low;
};

IPv6Mask prefixToIPv6Mask(int prefixLength)
{
    if (prefixLength < 0 || prefixLength > 128)
        throw std::invalid_argument("Invalid IPv6 prefix length");

    IPv6Mask mask{0, 0};

    if (prefixLength == 0) {
        return mask;
    }

    if (prefixLength < 64) {
        mask.high = UINT64_MAX << (64 - prefixLength);
        mask.low = 0;
    }
    else if (prefixLength == 64) {
        mask.high = UINT64_MAX;
        mask.low = 0;
    }
    else {
        mask.high = UINT64_MAX;
        mask.low = UINT64_MAX << (128 - prefixLength);
    }

    return mask;
}
struct IPv6Address {
    std::uint64_t high;
    std::uint64_t low;
};

IPv6Address ipv6ToUint64(const std::string& ip)
{
    unsigned char bytes[16];

    if (inet_pton(AF_INET6, ip.c_str(), bytes) != 1) {
        throw std::invalid_argument("Invalid IPv6 address");
    }

    std::uint64_t high = 0;
    std::uint64_t low = 0;

    for (int i = 0; i < 8; ++i) {
        high = (high << 8) | bytes[i];
    }

    for (int i = 8; i < 16; ++i) {
        low = (low << 8) | bytes[i];
    }

    return {high, low};
}

//MAIN CODE
RouteTable::RouteTable(){
    _routes = {};
}

void RouteTable::add_route(const Route& route){
    for(size_t i = 0; i < _routes.size(); i++){
        if(_routes[i].get_destination() == route.get_destination() && 
        _routes[i].get_gateway() == route.get_gateway() && 
        _routes[i].get_interface_name() == route.get_interface_name() &&
        _routes[i].get_prefix_length() == route.get_prefix_length()) 
        return;
    }
    
    _routes.push_back(route);
}

bool RouteTable::remove_route(const Route& route){
    for(size_t i = 0; i < _routes.size(); i++){
        if(_routes[i].get_destination() == route.get_destination() && 
        _routes[i].get_gateway() == route.get_gateway() && 
        _routes[i].get_interface_name() == route.get_interface_name() &&
        _routes[i].get_prefix_length() == route.get_prefix_length()){
            _routes.erase(_routes.begin() + i);
            return true;
        }
    }


    return false;
}

const Route* RouteTable::find_route(const std::string& destIp) const
{
    if (destIp.empty())
        return nullptr;

    bool isIpv4 = IpHelper::isIPv4(destIp);
    bool isIpv6 = IpHelper::isIPv6(destIp);

    if (!isIpv4 && !isIpv6)
        return nullptr;

    const Route* bestRoute = nullptr;
    int bestPrefixLength = -1;


    // ============================================================
    // IPv4 ROUTE LOOKUP
    // ============================================================
    if (isIpv4)
    {

        std::uint32_t destination = ipv4ToUint32(destIp);

        for (const auto& currentRoute : _routes)
        {
            if (!isIPv4(currentRoute.get_destination()))
                continue;

            std::uint8_t prefixLength = currentRoute.get_prefix_length();

            if (prefixLength > 32)
                continue;

            std::uint32_t routeNetwork =
                ipv4ToUint32(currentRoute.get_destination());

            std::uint32_t subnetMask;

            if (prefixLength == 0)
            {
                subnetMask = 0;
            }
            else
            {
                subnetMask =
                    0xFFFFFFFFu << (32 - prefixLength);
            }

            if ((destination & subnetMask) ==
                (routeNetwork & subnetMask))
            {
                if (prefixLength > bestPrefixLength)
                {
                    bestPrefixLength = prefixLength;
                    bestRoute = &currentRoute;
                }
            }
        }

        return bestRoute;
    }


    // ============================================================
    // IPv6 ROUTE LOOKUP
    // ============================================================
    if (isIpv6)
    {
        IPv6Address destination = ipv6ToUint64(destIp);

        for (const auto& currentRoute : _routes)
        {
            if (!isIPv6(currentRoute.get_destination()))
                continue;

            std::uint8_t prefixLength = currentRoute.get_prefix_length();

            if (prefixLength > 128)
                continue;

            IPv6Address routeNetwork =
                ipv6ToUint64(currentRoute.get_destination());

            IPv6Mask subnetMask =
                prefixToIPv6Mask(prefixLength);

            if (((destination.high & subnetMask.high) ==
                 (routeNetwork.high & subnetMask.high)) &&
                ((destination.low & subnetMask.low) ==
                 (routeNetwork.low & subnetMask.low)))
            {
                if (prefixLength > bestPrefixLength)
                {
                    bestPrefixLength = prefixLength;
                    bestRoute = &currentRoute;
                }
            }
        }

        return bestRoute;
    }

    return nullptr;
}

const std::vector<Route>& RouteTable::get_routes() const{
    return _routes;
}

void RouteTable::clear(){
    _routes.clear();
}