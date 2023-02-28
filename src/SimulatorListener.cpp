#include "include/Listener.hpp"

class SimulatorListener
{
private:
    std::unique_ptr<Listener> activeSimulationListener;
public:
    SimulatorListener(/* args */);
    ~SimulatorListener();
    
    void OnSimulationStart(){};
    void OnSimulationEnd(){};
    void OnSimulationUpdate(){};
    void OnSimulationResult(){};
    void SetListener(){};
};

SimulatorListener::SimulatorListener(/* args */)
{
}

SimulatorListener::~SimulatorListener()
{
}
