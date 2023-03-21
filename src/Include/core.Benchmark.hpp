#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include "core.Types.hpp"
#include "SimulatorMockUpInterface.hpp"
#include "core.Scenario.hpp"
#include <./yaml-cpp/yaml.h>

//! Benchmark class
/*!
    This class is responsible for managing the simulation scenarios.
    It is responsible for creating, removing, and running scenarios.
*/
class Benchmark {
private:
    std::map<std::string, std::unique_ptr<Scenario>> scenarios;

    /*Yaml::Node*/

    /*
    ????
    struct ExecutionStrategy {
        std::string name;
        std::vector<std::string> scenarios;
    };
    */

public:
    Benchmark(){};
    ~Benchmark(){};

    void LoadSimulationConfig(std::string configPath);

    /*ExecutionStrategy CreateExecutionStrategy(std::vector<std::string> scenarios){}; ???? */ 

    void CreateScenario(std::string scenarioName);

    void RemoveScenario(std::string scenarioName);

    void mapScenarioToParameter(std::string scenarioName, Parameter parameter);
    void mapScenarioToMetrics(std::string scenarioName, std::map<std::string, Metrics> metrics);

    void RunScenario(std::string ScenarioName);

    std::vector<std::string> RunScenariosWithParameters(std::map<std::string, Scenario> scenarios);

    std::vector<std::string> RunScenarioUsingStrategy(std::map<std::string, Scenario>, size_t executionStrategy);
};


#endif