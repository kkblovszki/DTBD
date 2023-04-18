#include "Include/Parser.hpp"

void Parser::parseScenario(const YAML::Node& scenarioNode, ScenarioDescriptor& scenario) {
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

void Parser::parseSimulationStrategy(const YAML::Node& simulationStrategyNode, SimulationStrategy& simulationStrategy) {
    simulationStrategy.multithread = simulationStrategyNode["multithread"].as<bool>();
    simulationStrategy.threadNr = simulationStrategyNode["thread_nr"].as<int>();
    const auto& executionOrderNode = simulationStrategyNode["ExecutionOrder"];
    for (const auto& it : executionOrderNode) {
        simulationStrategy.executionOrder[it.first.as<int>()] = it.second.as<std::string>();
    }
}

/**
 * @brief 
 * This function takes an entire benchmarks and parses it into cpp objects, to standardise the data through the framework.
 * This is done to ensure simple rules in the YAML configuration file is followed.
 * 
 * If we find the simulation strategy we parse it into a SimulationStrategy object.
 * If we find the simulator we parse each scenario in this simulator node into a ScenarioType object.
 * 
 * @param benchmarkNode 
 * @param benchmark 
 */
void Parser::parseBenchmark(const YAML::Node& benchmarkNode, std::map<std::string, ScenarioDescriptor>& ScenarioDescriptors, SimulationStrategy& simulationStrategy) {
    if (benchmarkNode["SimulationStrategy"]) {
        const auto& simulationStrategyNode = benchmarkNode["SimulationStrategy"];
        parseSimulationStrategy(simulationStrategyNode, simulationStrategy);
    }else if(benchmarkNode["Simulators"]) {
        const auto& scenariosNode = benchmarkNode["Scenarios"];
        for (const auto& it : scenariosNode) {
            ScenarioDescriptor scenario;
            parseScenario(it.second, scenario);
            ScenarioDescriptors[it.first.as<std::string>()] = scenario;
        }
    }
}