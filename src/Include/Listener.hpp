#ifndef LISTENER_HPP
#define LISTENER_HPP
#include "core.Types.hpp"

class Listener {
private:
    
public:
    Listener();
    ~Listener();
    
    virtual void OnSimulationStart() = 0;
    virtual void OnSimulationEnd() = 0;
    virtual void OnSimulationUpdate(std::function<void(double)> callback) = 0;
    virtual void OnSimulationResult() = 0;
};

Listener::Listener() {

}

Listener::~Listener() {

}

#endif