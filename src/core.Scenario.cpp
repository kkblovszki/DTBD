#include "Include/core.Scenario.hpp"
#include <cassert>

/**
 * @brief Construct a new Scenario:: Scenario object
 * @details This constructor is used when the scenario is created from the benchmark.
 * this specific constructor is used when no build options are specified. 
 * @param uniqueName 
 * @param simulatorType
 * @param simulatorVersion
 * @param ListenerType 
 */
Scenario::Scenario(std::string uniqueName, std::string& simulatorType, const std::string& simulatorVersion, const std::string& listenerType) : scenarioName(uniqueName) {
    
    std::cout << "Loading configuration for simulator version: " << simulatorVersion << std::endl;

    // create new listener instance
    std::unique_ptr<Listener> newSimulatorListener = ListenerCreator::CreateListener(listenerType);

    // create new simulator instance 
    SimulatorInstance = SimulatorCreator::CreateSimulator(simulatorType);

    // connect that listener to the simulator active listener the function is setListener and it takes a std::unique_ptr<Listener> as parameter
    SimulatorInstance->SetListener(std::move(newSimulatorListener));

    /*In the prepare simulation the config file from the benchmark is */
    try
    {
        SimulatorInstance->LoadConfiguration(simulatorVersion);
    }
    catch(const std::runtime_error& e)
    {   
        std::cerr << e.what() << '\n';
        std::terminate();
    }
}

/**
 * @brief Construct a new Scenario:: Scenario object
 * @details This constructor is used when the scenario is created from the benchmark.
 * This specific constructor is used when build options are specified.
 * @param uniqueName 
 * @param simulatorType 
 * @param simulatorVersion 
 * @param buildOptions 
 * @param listenerType 
 */
Scenario::Scenario(std::string uniqueName, std::string& simulatorType, const std::string& simulatorVersion, const std::vector<BuildOptions>& buildOptions, const std::string& listenerType) : scenarioName(uniqueName) {

    std::cout << "Loading configuration for simulator version: " << simulatorVersion << std::endl;

    // create new listener instance
    std::unique_ptr<Listener> newSimulatorListener = ListenerCreator::CreateListener(listenerType);

    // create new simulator instance 
    SimulatorInstance = SimulatorCreator::CreateSimulator(simulatorType);

    // Add the build options to the simulator
    SimulatorInstance->AddBuildOptions(buildOptions);

    // connect that listener to the simulator active listener the function is setListener and it takes a std::unique_ptr<Listener> as parameter
    SimulatorInstance->SetListener(std::move(newSimulatorListener));

    /*In the prepare simulation the config file from the benchmark is */
    try
    {
        SimulatorInstance->LoadConfiguration(simulatorVersion);
    }
    catch(const std::runtime_error& e)
    {   
        std::cerr << e.what() << '\n';
        std::terminate();
    }
}

Scenario::~Scenario(){}

/**
 * @brief Prepare the simulation with the given metrics and parameters
 * @param metrics 
 * @param parameters 
 * @param Strategy 
 */
void Scenario::PrepareSimulation(const std::vector<Metrics>& metrics, const std::vector<Parameter>& parameters) {
    std::vector<Metrics> metricsToLoad = metrics;
    std::vector<Parameter> parametersToLoad = parameters;
    
    // load the metrics to the simulator
    SimulatorInstance->LoadMetrics(metricsToLoad);
    // load the parameters to the simulator
    SimulatorInstance->LoadParameters(parametersToLoad);
    return;
}
