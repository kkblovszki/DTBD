#include "Include/core.Scenario.hpp"
#include <cassert>

/**
 * @brief Construct a new Scenario:: Scenario object
 * 
 * @param uniqueName 
 * @param simulatorType 
 * @param ListenerType 
 */
Scenario::Scenario(std::string uniqueName, std::string simulatorType, std::string ListenerType) : scenarioName(uniqueName) {
    // create new listener instance
    std::unique_ptr<Listener> newSimulatorListener = ListenerCreator::CreateListener(ListenerType);

    std::cout << "Testing if listener creation fails: ";
    newSimulatorListener->OnSimulationResult();
    std::cout << "it doesn't" << std::endl;

    // check if the listener is of type Listener
    //static_assert(std::is_same_v<decltype(activeSimulatorListener), std::unique_ptr<Listener>>);

    // create new simulator instance 
    Simulator = SimulatorCreator::CreateSimulator(simulatorType);

    // connect that listener to the simulator active listener the function is setListener and it takes a std::unique_ptr<Listener> as parameter
    Simulator->SetListener(std::move(newSimulatorListener));

}

Scenario::~Scenario(){
    return;
}


/**
 * @brief Prepare the simulation for the given strategy
 *  This function is used to prepare the simulation for the given strategy
 * @param Strategy 
 */
void Scenario::PrepareSimulation(std::map<std::string, size_t> Strategy) {
    return;
}