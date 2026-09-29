#pragma once
#include <string>
class IpHelper{
    public:
        static bool isIPv4(const std::string& s);
        static bool isIPv6(const std::string& s);
};