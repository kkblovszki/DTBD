#include "Include/core.Benchmark.hpp"
#include "core.Benchmark.hpp"

/**
 * @brief Loads the simulation configuration file
 * @details The simulation configuration file is a YAML file that contains the simulation scenarios and their respective simulation strategies.
 * The simulation configuration file is loaded into a YAML::Node object and then parsed using the @Parser class.
 * @param configPath - the path to the simulation configuration file
 * @throws std::runtime_error if the simulation configuration file is not found
 * @throws std::runtime_error if the simulation configuration file is empty
 * @throws std::runtime_error if the simulation configuration file is not a valid YAML file
 * @returns void
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
 * @param scenarioName - the name of the scenario to be created
 * @details The @param scenarioName must match the name of the scenario in the simulation configuration file.
 * It iterates through the simulations in the config file and creates a single scenario at a time, based on the scenario name, simulator type, and listener type.
 * However the listener type is optional and can be added later by manually creating a listener object and adding it to the scenario using the @SimulatorMockupInterface's SetListener method
 * 
 * @returns void
 * 
 * @throws std::runtime_error if the scenario name already exists
 * @throws std::runtime_error if the scenario name does not match any scenario in the simulation configuration file
 * @throws std::runtime_error if the simulator type is not defined in the simulation configuration file
 */
void Benchmark::CreateScenario(std::string scenarioName){
    
    /* --- Perform checks --- */
     
    //Check if scenario already exists
    if (scenarios.find(scenarioName) != scenarios.end()) {
        std::cerr << "Error: Scenario " << scenarioName << " already exists.\n";
        return;
    }

    //Check to see if the scenario exists in the config file
    if (scenariosDescriptors.find(scenarioName) == scenariosDescriptors.end()) {
        //std::cerr << "Error: Scenario " << scenarioName << " not found in config file.\n";
        throw std::runtime_error("Scenario not found in config file: " + scenarioName); 
        return;
    }

    std::string simulatorType = scenariosDescriptors[scenarioName].simulator;
    std::string simulatorVersion = scenariosDescriptors[scenarioName].simulatorVersion;

    if(simulatorType == ""){
        throw std::runtime_error("Simulator type is undefined found for scenario: " + scenarioName + ".\n" + "Please check the simulation configuration file.\n" + "Exiting scenario creation\n");
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
 * @brief Creates all scenarios in the config file
 * @details Iterates through the scenarios in the benchmark config file and creates a single scenario at a time, or type, and listener type.
 * However the listener type is optional and can be added later by manually based on the scenario name, simulatreating a listener object and adding it to the scenario using the @SimulatorMockupInterface's SetListener method
 * @returns void
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
 * @brief Removes a scenario from the map of scenarios
 * @details The @param scenarioName must match the name of the scenario in the simulation configuration file.
 * @param scenarioName 
 * @returns void
 */
void Benchmark::RemoveScenario(std::string scenarioName){
    //delete instance from memory and remove from map
    scenarios[scenarioName].reset();
    scenarios.erase(scenarioName);
    return;
};

/**
 * @brief Runs a specific scenario
 * @details The @param scenarioName must match the name of the scenario in the simulation configuration file.
 * @param ScenarioName
 * @returns void 
 */
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


/**
 * @brief Runs a specific scenario with parameters
 * @details The @param scenarioName must match the name of the scenario in the simulation configuration file, and the parameters must be supported by the specified simulator.
 * @param ScenarioName 
 * @returns void
 */
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
 * @brief Runs a specific scenario with a specific strategy defined in the config file
 * @details The @param scenarioName must match the name of the scenario in the simulation configuration file, and the strategy must be defined in the config file.
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