#ifndef ABSTRACT_LISTENER_HPP
#define ABSTRACT_LISTENER_HPP

#include "core.Types.hpp"

class Listener {
public:
    Listener(){};
    ~Listener(){};
    
    Measure measurements;

    virtual void OnSimulationStart(std::vector<Metrics> metrics) = 0;
    virtual void OnSimulationEnd() = 0;
    virtual void OnSimulationUpdate() = 0;
    virtual void OnSimulationResult() = 0;
};

#endif