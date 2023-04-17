#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <./yaml-cpp/yaml.h>
#include "core.Types.hpp"
#include "SimulatorMockUpInterface.hpp"
#include "core.Scenario.hpp"
#include "Parser.hpp"

/**
 * @brief Benchmark class
 * This class is responsible for managing the simulation scenarios.
 * It is responsible for creating, removing, and running scenarios.
 */
class Benchmark {
private:

    #ifndef DEBUG
    std::map<std::string, std::unique_ptr<Scenario>> scenarios;
    #endif

    std::map<std::string, std::string> config;
    
    std::map<std::string, ScenarioDescriptor> scenariosDescriptors;
    SimulationStrategy simulationStrategiesDescriptors;

public:
    Benchmark(){};
    ~Benchmark(){};

    #ifdef DEBUG
    std::map<std::string, std::unique_ptr<Scenario>> scenarios;
    #endif

    /**
    * @brief 
    * Using the library yaml-cpp, load the simulation configuration file and store the data in the Benchmark object
    * convert the config into an accessable ordered map, to get the individual simulations names, get the simulator type, and the listener type
    * Runs the parser @ref parseScenario, @ref parseSimulator, and @ref parseListener to parse the simulation configuration file into a predetermined format, with a ruleset. 
    * @param configPath 
    */
    void LoadSimulationConfig(std::string configPath); 


    /**
     * @brief Create a Scenario object
     * 
     * @param scenarioName 
     */
    void CreateScenario(std::string scenarioName);

    /**
     * @brief Remove a Scenario object
     * 
     * @param scenarioName 
     */
    void RemoveScenario(std::string scenarioName);
    
    
    void mapScenarioToParameter(std::string scenarioName, Parameter parameter);
    void mapScenarioToMetrics(std::string scenarioName, std::map<std::string, Metrics> metrics);

    /**
     * @brief 
     * 
     * @param ScenarioName 
     */
    void RunScenario(std::string ScenarioName);

    /**
     * @brief 
     * 
     * @param scenarios 
     * @return std::vector<std::string> 
     */
    std::vector<std::string> RunScenariosWithParameters(std::map<std::string, Scenario> scenarios);

    /**
     * @brief 
     * 
     * @param scenarios 
     * @param executionStrategy 
     * @return std::vector<std::string> 
     */
    std::vector<std::string> RunScenarioUsingStrategy(std::map<std::string, Scenario>, size_t executionStrategy);

    /*ExecutionStrategy CreateExecutionStrategy(std::vector<std::string> scenarios){}; ???? */
};


#endif