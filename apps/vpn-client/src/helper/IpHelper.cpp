#include "IpHelper.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <arpa/inet.h>


bool IpHelper::isIPv4(const std::string& s)
{
    int cnt = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '.')
            cnt++;
    }

    if (cnt != 3)
        return false;

    std::vector<std::string> tokens;

    std::stringstream check1(s);
    std::string intermediate;

    while (getline(check1,
                   intermediate, '.')) {
        tokens.push_back(intermediate);
    }

    if (tokens.size() != 4)
        return false;

    for (int i = 0; i < tokens.size(); i++) {
        int num = 0;

        if (tokens[i] == "0")
            continue;

        if (tokens[i].size() == 0)
            return false;

        for (int j = 0;
             j < tokens[i].size();
             j++) {
            if (tokens[i][j] > '9'
                || tokens[i][j] < '0')
                return false;

            num *= 10;
            num += tokens[i][j] - '0';

            if (num == 0)
                return false;
        }

        if (num > 255 || num < 0)
            return false;
    }

    return true;
}

bool IpHelper::isIPv6(const std::string& s){
    struct in6_addr result{};
    return inet_pton(AF_INET6, s.c_str(), &result) == 1;
}
