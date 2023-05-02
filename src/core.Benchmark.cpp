#include "Include/core.Benchmark.hpp"
#include "core.Benchmark.hpp"

/**
 * @brief 
 * @param configPath 
 */
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

    if(simulatorType == ""){
        std::cerr << "Error - Simulator type is undefined found for scenario: " << scenarioName << ".\n";
        std::cerr << "Please check the simulation configuration file.\n";
        std::cerr << "Exiting scenario creation\n";
        return;
    }

    //Check if listener type is valid
    std::string listenerType;

    if(scenariosDescriptors[scenarioName].listener == ""){
        listenerType = "ConsoleListener";
    }else{
        listenerType = scenariosDescriptors[scenarioName].listener;
    }
    
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
    return;
};

/**
 * @brief 
 * Creates all scenarios in the config file
 * @details 
 * Iterates through the scenarios in the benchmark config file and creates a single scenario at a time, or type, and listener type.
 * \n
 * However the listener type is optional and can be added later by manually based on the scenario name, simulatreating a listener object and adding it to the scenario using the @SimulatorMockupInterface's SetListener method
 */
void Benchmark::CreateAllScenarios()
{   
    // Iterate over all scenarios in the map
    for (auto& [scenarioName, scenario] : scenariosDescriptors) {
        CreateScenario(scenarioName);
    }
    return;
};

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
        throw std::runtime_error("Scenario not found: " + ScenarioName);
        return;
    }

    Scenario& scenario = *(it->second); //Found scenario
    scenario.SimulatorInstance->RunSimulation(); //Run the simulation
    return;
};



void Benchmark::RunScenarioWithParameters(std::string ScenarioName){
    auto it = scenarios.find(ScenarioName);
    if (it == scenarios.end()) {
        throw std::runtime_error("Scenario not found: " + ScenarioName);
        return;
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

    return;
};

/**
 * @brief 
 * Implements the RunScenarioWithStrategy function from the BenchmarkInterface
 * by using the strategy specified in the config file
 * @return std::vector<std::string> A vector of strings containing the names of the scenarios that failed to run
 */
std::vector<std::string> Benchmark::RunScenariosUsingStrategy(){
    
    //check if a strategy is defined 
    if(simulationStrategiesDescriptors.multithread == false && simulationStrategiesDescriptors.executionOrder.empty()){
        std::cerr << "No strategy defined in config file - Please define a strategy in the config file." << std::endl;
        return std::vector<std::string>();
    }

    std::vector<std::string> failedScenarios;

    // Iterate over all scenarios in the map and run them using the strategy defined in the config file
    for(auto& [_ ,scenarioName] : simulationStrategiesDescriptors.executionOrder){
        try {
            // Prepare the simulation using the specified metrics and parameters
            const std::vector<Parameter> parameters = scenariosDescriptors[scenarioName].parameters;
            const std::vector<Metrics> metrics = scenariosDescriptors[scenarioName].metrics;
            scenarios[scenarioName]->PrepareSimulation(metrics, parameters);

            // Run the simulation
            scenarios[scenarioName]->SimulatorInstance->RunSimulation();
        }   
        catch (const std::exception& e) {
            std::cerr << "Error running scenario " << scenarioName << ": " << e.what() << std::endl;
            failedScenarios.push_back(scenarioName);
        }
    }
    
    return failedScenarios;
};