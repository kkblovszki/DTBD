#include "Include/core.Benchmark.hpp"
#include "core.Benchmark.hpp"


void Benchmark::LoadSimulationConfig(std::string configPath){
    
    YAML::Node config_ = YAML::LoadFile(configPath);

    if(config_.IsNull()){
        throw std::runtime_error("Config file not found");
    }

    Parser::parseBenchmark(config_, scenariosDescriptors, simulationStrategiesDescriptors);    

    std::cout << "Config loaded" << std::endl;
};

/**
 * @brief Creates a scenario object and adds it to the map of scenarios
 * It iterates through the simulations in the config file and creates a single scenario at a time, based on the scenario name, simulator type, and listener type.
 * \n
 * However the listener type is optional and can be added later by manually creating a listener object and adding it to the scenario using the @SimulatorMockupInterface's SetListener method
 * @details The @param scenarioName must match the name of the scenario in the simulation configuration file
 */
void Benchmark::CreateScenario(std::string scenarioName){
    
    /* --- Perform checks --- */
     
    //Check if scenario already exists
    if (scenarios.find(scenarioName) != scenarios.end()) {
        std::cerr << "Error: Scenario " << scenarioName << " already exists.\n";
        return;
    }/*else if (scenariosDescriptors.find(scenarioName) == scenariosDescriptors.end()) {
        std::cerr << "Error: Scenario " << scenarioName << " not found in config file.\n";
        return;
    }*/ //This makes it unable to run some basic framework tests since it needs the parser to work.

    std::string simulatorType = scenariosDescriptors[scenarioName].simulator;
    std::string simulatorVersion = scenariosDescriptors[scenarioName].simulatorVersion;

    
    #ifdef DEBUG
        simulatorType = "ns3"; //currently only ns3 is even remotely supported
        simulatorVersion = "3.38"; //ns3 version for debugging.
        std::cout << "Debug mode - Simulator type set to: " << simulatorType << std::endl;
    #else
    //Check if simulator type is valid
    if(simulatorType == ""){
        std::cerr << "Error - Simulator type is undefined found for scenario: " << scenarioName << ".\n";
        std::cerr << "Please check the simulation configuration file.\n";
        std::cerr << "Exiting scenario creation\n";
        return;
    }
    #endif

    std::cerr << "Simulator: " << simulatorType << std::endl;
    std::cerr << "Version: " << simulatorVersion << std::endl;


    //Check if listener type is valid
    std::string listenerType;

    if(scenariosDescriptors[scenarioName].listener == ""){
        listenerType = "ConsoleListener";
    }else{
        listenerType = scenariosDescriptors[scenarioName].listener;
    }

    std::cout << "Listener: " << listenerType << std::endl;

    //For when multi listeners gets supported
    /*for(auto it = scenariosDescriptors.begin(); it != scenariosDescriptors.end(); ++it){
        if(it->first == scenarioName){
            if(it->second.listener != ""){
                listener = std::make_shared<Listener>(it->second.listener);
            }
        }
    }*/
    
    std::unique_ptr<Scenario> singleScenario = nullptr;

    //Check if build options are defined
    if(scenariosDescriptors[scenarioName].buildOptions.size() == 0){
         // Create scenario
         singleScenario = std::make_unique<Scenario>(scenarioName, simulatorType, simulatorVersion, listenerType);
    }else{
         // Create scenario
        singleScenario = std::make_unique<Scenario>(
            scenarioName, 
            simulatorType, 
            simulatorVersion, 
            scenariosDescriptors[scenarioName].buildOptions,
            listenerType);
    }

    // Add scenario to map
    scenarios.insert(std::make_pair(scenarioName, std::move(singleScenario)));
};

/*
void Benchmark::CreateAllScenarios()
{
    YAML::Node simulationProfiles = config_["SimulationProfile"];
    if (!simulationProfiles) {
        std::cerr << "No simulation profiles found." << std::endl;
        return;
    }

    for (auto it = simulationProfiles.begin(); it != simulationProfiles.end(); ++it) {
        std::string scenarioName = it->first.as<std::string>();
        CreateScenario(scenarioName);
    }
}*/

/**
 * @brief 
 * Removes a scenario from the map of scenarios
 * @param scenarioName 
 */
void Benchmark::RemoveScenario(std::string scenarioName){
    //delete instance from memory and remove from map
    scenarios[scenarioName].reset();
    scenarios.erase(scenarioName);
    return;
};

//using the scenarioName given as a string and run the scenario
void Benchmark::RunScenario(std::string ScenarioName){

    auto it = scenarios.find(ScenarioName);
    if (it == scenarios.end()) {
        std::cerr << "Scenario " << ScenarioName << " not found." << std::endl;
        return;
    }

    Scenario& scenario = *(it->second); //Found scenario
    scenario.SimulatorInstance->RunSimulation(); //Run the simulation
    return;
};

std::vector<std::string> Benchmark::RunScenarioWithParameters(std::string ScenarioName){
    auto it = scenarios.find(ScenarioName);
    if (it == scenarios.end()) {
        std::cerr << "Scenario " << ScenarioName << " not found." << std::endl;
        return std::vector<std::string>();
    }

    Scenario& scenario = *(it->second); //Found scenario

    /*
    Currently the parameters are converted to const, then back to non-const.
    The parameters themselves are not changed, only the "constness". since manipulating the data in the scenarioDescriptor is not allowed in the code.
    This is done to have a default values in the preparesimulation functions arguments
    There is must be a smarter way to do this. 
    */
    const std::vector<Parameter> parameters = scenariosDescriptors[ScenarioName].parameters; 
    scenario.PrepareSimulation( {}, parameters ); //Prepare the simulation create function that only loads the metrics and parameters
    scenario.SimulatorInstance->RunSimulation(); //Run the simulation

return std::vector<std::string>();
};


std::vector<std::string> Benchmark::RunScenariosUsingStrategy(){
    throw std::runtime_error("Not implemented");

    //TODO: Implement this - using the strategy given in the config file: SimulationStrategy
    /*
    std::vector<std::string> failedScenarios;

    // Iterate over all scenarios in the map
    for (auto& [scenarioName, scenario] : scenarios) {
        try {
            // Prepare the simulation using the specified strategy
            scenario->PrepareSimulation({{"strategy", executionStrategy}});

            // Run the simulation
            scenario->Simulator->RunSimulation();

            // Get the simulation results
            std::vector<std::size_t> results = scenario->Simulator->GetSimulationResults();

            // Update the scenario's metrics with the simulation results
            for (std::size_t i = 0; i < results.size(); ++i) {
                scenario->metrics["metric_" + std::to_string(i)] = Metrics(results[i]);
            }
            
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error running scenario " << scenarioName << ": " << e.what() << std::endl;
            failedScenarios.push_back(scenarioName);
        }

        return failedScenarios
    }*/
};