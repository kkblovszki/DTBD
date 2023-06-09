#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <./yaml-cpp/yaml.h>
#include "core.Types.hpp"
#include "SimulatorMockUpInterface.hpp"
#include "core.Scenario.hpp"
#include "Parser.hpp"

/**
 * @page BenchmarkPage Benchmark
 * 
 * @section Benchmark 
 * 
 * @brief Benchmark documentation.
 * 
 * This is the Benchmark class. It does some things and has some properties..
 */
class Benchmark {
private:

    /* Remove this after debugging to use the private variables 
    std::map<std::string, std::unique_ptr<Scenario>> scenarios;
    std::map<std::string, ScenarioDescriptor> scenariosDescriptors;
    SimulationStrategy simulationStrategiesDescriptors;
    */

public:
    Benchmark(){};
    ~Benchmark(){};

    /*only for behavioral debugging must be moved into private */
    std::map<std::string, std::unique_ptr<Scenario>> scenarios;
    std::map<std::string, ScenarioDescriptor> scenariosDescriptors;
    SimulationStrategy simulationStrategiesDescriptors;

    /**
    * @brief 
    * Using the library yaml-cpp, load the simulation configuration file and store the data in the Benchmark object
    * convert the config into an accessable ordered map, to get the individual simulations names, get the simulator type, and the listener type
    * Runs the parser @ref parseScenario, @ref parseSimulator, and @ref parseListener to parse the simulation configuration file into a predetermined format, with a ruleset. 
    * @param configPath 
    */
    void LoadSimulationConfig(std::string configPath); 

    /**
     * @brief Create a Scenario object and add it to the map of scenarios
     * @param scenarioName 
     */
    void CreateScenario(std::string scenarioName);

    /**
     * @brief Create all Scenario objects in the config file and add them to the map of scenarios
     */
    void CreateAllScenarios();

    /**
     * @brief Remove a Scenario object
     * @param scenarioName 
     */
    void RemoveScenario(std::string scenarioName);

    /**
     * @brief Run a Scenario object
     * @param ScenarioName 
     */
    void RunScenario(std::string ScenarioName);

    /**
     * @brief 
     * @param ScenarioName 
     */
    void RunScenarioWithParameters(std::string ScenarioName);

    /**
     * @brief 
     * Runs the scenarios using the strategy defined in the simulation configuration file
     * @details 
     * @param scenarios 
     * @param executionStrategy 
     * @return std::vector<std::string> 
     */
    std::vector<std::string> RunScenariosUsingStrategy();
};


#endif