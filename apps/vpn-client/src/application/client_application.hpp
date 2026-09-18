#pragma once


#include "../connection/connection_manager.hpp"
#include "../networking/udp_endpoint.hpp"

class ClientApplication {
public:
    ClientApplication();

    void run();
    void stop();
};