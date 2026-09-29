#pragma once

#include <cstdint>
#define _FAILURE_THRESHOLD_COUNTER 3
class HealthMonitor{
    private:
        bool _isHealthy;
        std::uint32_t _failure_threshold_counter;
    public:

    HealthMonitor();

    void record_success();
    void record_failure();
    const bool is_healthy() const;
    void reset();

};