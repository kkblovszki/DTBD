#include "Include/core.Benchmark.hpp"

/**
 * @brief 
 * Using the library yaml-cpp, load the simulation configuration file and store the data in the Benchmark object
 * convert the config into an accessable ordered map, to get the individual simulations names, get the simulator type, and the listener type
 * @param configPath 
 */
void Benchmark::LoadSimulationConfig(std::string configPath){
    
    YAML::Node config_ = YAML::LoadFile(configPath);

    if(config_.IsNull()){
        throw std::runtime_error("Config file not found");
    }

    config = YAMLNodeToMap(config_);    
    
    std::cout << "Config loaded" << std::endl;
};

/**
 * @brief Creates a scenario object and adds it to the map of scenarios
 * it iterates through the simulations in the config file and creates a single scenario at a time, based on the scenario name, simulator type, and listener type
 * However the listener type is optional and can be added later by manually creating a listener object and adding it to the scenario using the @SimulatorMockupInterface's SetListener method
 * @param scenarioName 
 */
void Benchmark::CreateScenario(std::string scenarioName){
    /* 
    YAML::Node simulationProfiles = config_["SimulationProfile"];
    YAML::Node scenarioConfig = simulationProfiles[scenarioName];

    // Check if scenario already exists
    if (scenarios_.find(scenarioName) != scenarios_.end()) {
        std::cerr << "Error: Scenario " << scenarioName << " already exists.\n";
        return;
    }

    //Get the simulator type written in the yaml file
    std::string simulatorType = scenarioConfig["SimulatorType"].as<std::string>();

    // Create listener if specified
    std::shared_ptr<ListenerInterface> listener;
    if (scenarioConfig["ListenerType"]) {
        std::string listenerType = scenarioConfig["ListenerType"].as<std::string>();
    }
    
    // Create scenario
    std::unique_ptr<Scenario> singleScenario = std::make_unique<Scenario>(scenarioName, simulatorType, listenerType);

    // Add scenario to map
    scenarios.insert(std::make_pair(scenarioName, std::move(singleScenario)));
    */
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
 * 
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
    scenarios[scenarioName]->metrics = metrics;
};


//using the scenarioName given as a string and run the scenario
void Benchmark::RunScenario(std::string ScenarioName){
    /*
    auto it = scenarios.find(scenarioName);
    if (it == scenarios.end()) {
        std::cerr << "Scenario " << scenarioName << " not found." << std::endl;
        return;
    }

    Scenario& scenario = *(it->second);
    scenario.PrepareSimulation({{"ExecutionStrategy", 1}});
    scenario.Simulator->RunSimulation();

    std::cout << "Scenario " << scenarioName << " completed." << std::endl;
    */
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