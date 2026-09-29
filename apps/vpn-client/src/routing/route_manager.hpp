#pragma once

#include "route.hpp"

#include <vector>

class RouteManager {
private:
    std::vector<Route> _routes;

public:
    RouteManager();

    void add_route(const Route& route);
    bool remove_route(const Route& route);
    bool has_route(const Route& route) const;

    const std::vector<Route>& get_routes() const;

    void clear();
};