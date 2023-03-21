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
    std::map<std::string, std::string> config;

    /*Yaml::Node*/

    /*
    ????
    struct ExecutionStrategy {
        std::string name;
        std::vector<std::string> scenarios;
    };
    */

    std::map<std::string, std::string> YAMLNodeToMap(const YAML::Node& node){
        std::map<std::string, std::string> map;
        for (auto it = node.begin(); it != node.end(); ++it) {
            std::string key = it->first.as<std::string>();
            std::string value = it->second.as<std::string>();
            map[key] = value;
        }
        return map;
    }

    /*
    void MapToYAML(const std::map<std::string, std::string>& map, const std::string& filename){
        YAML::Emitter out;
        out << YAML::BeginMap;
        for (auto const& pair : map) {
            out << YAML::Key << pair.first;
            out << YAML::Value << pair.second;
        }
        out << YAML::EndMap;
        std::ofstream file(filename);
        file << out.c_str();
    }*/


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