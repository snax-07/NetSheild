
#include "route_manager.hpp"

#include <algorithm>

RouteManager::RouteManager() = default;

void RouteManager::add_route(const Route& route) {
    if (has_route(route)) {
        return;
    }

    _routes.push_back(route);
}

bool RouteManager::remove_route(const Route& route) {
    auto it = std::find(_routes.begin(), _routes.end(), route);

    if (it == _routes.end()) {
        return false;
    }

    _routes.erase(it);
    return true;
}

bool RouteManager::has_route(const Route& route) const {
    return std::find(_routes.begin(), _routes.end(), route) != _routes.end();
}

const std::vector<Route>& RouteManager::get_routes() const {
    return _routes;
}

void RouteManager::clear() {
    _routes.clear();
}