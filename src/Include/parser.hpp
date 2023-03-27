#ifndef PARSER_HPP
#define PARSER_HPP

#include <yaml-cpp/yaml.h>
#include <iostream>
#include <core.Types.hpp>

class Parser {
public:
    Parser();
    ~Parser();

static void parseScenario(const YAML::Node& scenarioNode, Scenario& scenario) {
    scenario.name = scenarioNode["name"].as<std::string>();
    scenario.description = scenarioNode["description"].as<std::string>();
    scenario.simulator = scenarioNode["simulator"].as<std::string>();
    if (scenarioNode["optional"]) {
        const auto& optionalNode = scenarioNode["optional"];
        for (const auto& it : optionalNode) {
            scenario.optional[it.first.as<std::string>()] = it.second.as<std::string>();
        }
    }
    const auto& requiredNode = scenarioNode["required"];
    for (const auto& it : requiredNode) {
        if (it.Type() == YAML::NodeType::Map) {
            const auto& mapNode = it.second;
            for (const auto& it2 : mapNode) {
                scenario.required[it.first.as<std::string>() + "." + it2.first.as<std::string>()] = it2.second.as<std::string>();
            }
        } else if (it.Type() == YAML::NodeType::Scalar) {
            scenario.required[it.first.as<std::string>()] = it.second.as<std::string>();
        }
    }
    if (scenarioNode["Parameters"]) {
        const auto& parametersNode = scenarioNode["Parameters"];
        for (const auto& it : parametersNode) {
            Parameter parameter;
            parameter.name = it.first.as<std::string>();
            parameter.defaultParameter = it.second.as<std::size_t>();
            scenario.parameters.push_back(parameter);
        }
    }
    if (scenarioNode["BuildOptions"]) {
        const auto& buildOptionsNode = scenarioNode["BuildOptions"];
        for (const auto& it : buildOptionsNode) {
            BuildOptions buildOptions;
            buildOptions.buildOption = it.first.as<std::string>();
            buildOptions.buildOptionValue = it.second.as<std::string>();
            scenario.buildOptions.push_back(buildOptions);
        }
    }
}

static void parseSimulationStrategy(const YAML::Node& simulationStrategyNode, SimulationStrategy& simulationStrategy) {
    simulationStrategy.multithread = simulationStrategyNode["multithread"].as<bool>();
    simulationStrategy.threadNr = simulationStrategyNode["thread_nr"].as<int>();
    const auto& executionOrderNode = simulationStrategyNode["ExecutionOrder"];
    for (const auto& it : executionOrderNode) {
        simulationStrategy.executionOrder[it.first.as<int>()] = it.second.as<std::string>();
    }
}

static void parseBenchmark(const YAML::Node& benchmarkNode, Benchmark& benchmark) {
    if (benchmarkNode["SimulationStrategy"]) {
        const auto& simulationStrategyNode = benchmarkNode["SimulationStrategy"];
        parseSimulationStrategy(simulationStrategyNode, benchmark.simulationStrategy);
    }

};

#endif // PARSER_HPP