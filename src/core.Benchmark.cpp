#include "Include/core.Benchmark.hpp"


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
    
    /*Perform checks*/
     
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
    #else
    //Check if simulator type is valid
    if(simulatorType == ""){
        std::cerr << "Error - Simulator type is undefined found for scenario: " << scenarioName << ".\n";
        std::cerr << "Please check the simulation configuration file.\n";
        std::cerr << "Exiting scenario creation\n";
        return;
    }
    #endif

    //scenariosDescriptors[scenarioName].simulatorVersion = 3.38;

    std::cout << "Simulator: " << simulatorType << std::endl;
    std::cout << "Version: " << simulatorVersion << std::endl;

    std::string listenerType;

    #ifdef DEBUG //DEBUGGING test_listener for outputting to console
        listenerType = "testlistener";
    #else
        listenerType = scenariosDescriptors[scenarioName].listener;
    #endif

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
};

void Benchmark::mapScenarioToParameter(std::string scenarioName, Parameter parameter){
    //scenarios[scenarioName]->parameters = parameter;
    throw std::runtime_error("Not implemented");
};


//using the scenarioName given as a string, find the scenario in the map and add the metrics to it
void Benchmark::mapScenarioToMetrics(std::string scenarioName, std::map<std::string, Metrics> metrics){
    throw std::runtime_error("Not implemented");
    //scenarios[scenarioName]->metrics = std::copy(metrics.begin(), metrics.end(), scenarios[scenarioName]->metrics.begin());
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
};

std::vector<std::string> RunScenariosWithParameters(std::map<std::string, Scenario> scenarios){
     throw std::runtime_error("Not implemented");
};


std::vector<std::string> Benchmark::RunScenarioUsingStrategy(std::map<std::string, Scenario>, size_t executionStrategy){
    throw std::runtime_error("Not implemented");
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
}