#include "Include/core.Scenario.hpp"

Scenario::~Scenario(){}

Scenario::Scenario(std::string uniqueName, std::string simulatorType, std::string ListenerType) : scenarioName(uniqueName) {

    std::unique_ptr<Listener> newListener = ListenerCreator::CreateListener(ListenerType);

    // create new simulator instance 
    std::unique_ptr<SimulatorMockUpInterface> Simulator = SimulatorCreator::CreateSimulator(simulatorType);
    
    // connect that listener to the simulator active listener
    Simulator->SetListener(std::move(newListener));
}


void Scenario::PrepareSimulation(std::map<std::string, size_t> Strategy) {
    return;
}