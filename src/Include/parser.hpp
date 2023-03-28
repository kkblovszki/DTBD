#ifndef PARSER_HPP
#define PARSER_HPP

#include <./yaml-cpp/yaml.h>
#include <iostream>
#include <core.Types.hpp>

/**
 * @brief Implements parser functions for the YAML configuration files @ref parseScenario, @ref parseBenchmark @parseSimulationStrategy. 
 * 
 * Must follow the Main Rules of the YAML configuration file (which is so far): 
 * 1. If no benchmark exists no Simulator can be determined thus no scenario can be created. 
 * 2. A single benchmark must consist of atleast 1 simulator with 1 scenario connected. 
 * 3. The scenario must have atleast a name defined
 */
class Parser {
public:
    Parser();
    ~Parser();

static void parseBenchmark(const YAML::Node& benchmarkNode, std::map<std::string, ScenarioType>& ScenarioDescriptor, SimulationStrategy simulationStrategy);
static void parseSimulationStrategy(const YAML::Node& simulationStrategyNode, SimulationStrategy& simulationStrategy);
static void parseScenario(const YAML::Node& scenarioNode, ScenarioType& scenario);
};

#endif //PARSER_HPP