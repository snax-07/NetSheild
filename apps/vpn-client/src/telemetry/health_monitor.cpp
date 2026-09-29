#include "health_monitor.hpp"

HealthMonitor::HealthMonitor(){
    _isHealthy = true;
    _failure_threshold_counter = 0;
}

void HealthMonitor::record_success(){
    _failure_threshold_counter = 0;
    _isHealthy = true;
}

void HealthMonitor::record_failure(){
    _failure_threshold_counter++;
    if(_failure_threshold_counter >= _FAILURE_THRESHOLD_COUNTER){
        _isHealthy = false;
    }
}

const bool HealthMonitor::is_healthy() const{
    return _isHealthy;
}

void HealthMonitor::reset(){
    _isHealthy = true;
    _failure_threshold_counter = 0;
}