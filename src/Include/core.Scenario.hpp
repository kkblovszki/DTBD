#include "core.Types.hpp"
#include "SimulatorCreator.hpp"
#include "ListenerCreator.hpp"
#include "SimulatorMockUpInterface.hpp"

class Scenario {
public:
    const std::string scenarioName;
    std::map<std::string, Metrics> metrics;
    Parameter parameters; 
    //Scenario(): scenarioName(NULL){metrics = {}; parameters.name = 'NULL'; parameters.defaultParameter = 0; parameters.underTest = NULL;};
    Scenario(std::string uniqueName, std::string simulatorType, std::string ListenerType);

    ~Scenario();
    

    void PrepareSimulation(std::map<std::string, size_t> Strategy);
};

Scenario::~Scenario() {}

Scenario::Scenario(std::string uniqueName, std::string simulatorType, std::string ListenerType) : scenarioName(uniqueName) {

    std::unique_ptr<Listener> newListener = ListenerCreator::createListener(ListenerType);
    
    // create new simulator instance 
    std::unique_ptr<SimulatorMockUpInterface> Simulator = SimulatorCreator::CreateSimulator(simulatorType);
    
    // connect that listener to the simulator active listener
    Simulator->SetListener(std::move(newListener));
}


void Scenario::PrepareSimulation(std::map<std::string, size_t> Strategy) {
    return;
}