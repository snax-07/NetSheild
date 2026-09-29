#pragma once

#include "route.hpp"

#include <string>
#include <vector>

class RouteTable {
private:
    std::vector<Route> _routes;

public:
    RouteTable();

    void add_route(const Route& route);
    bool remove_route(const Route& route);

    const Route* find_route(const std::string& destination_ip) const;

    const std::vector<Route>& get_routes() const;

    void clear();
};