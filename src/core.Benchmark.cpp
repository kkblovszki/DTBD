#include "Include/core.Benchmark.hpp"

void Benchmark::LoadSimulationConfig(std::string configPath){
    throw std::runtime_error("Not implemented");
};

void Benchmark::CreateScenario(std::string scenarioName){
    //scenarios[scenarioName] = std::make_unique<Scenario>(scenarioName, "NS3", "DefaultListener");
    throw std::runtime_error("Not implemented");
};

void Benchmark::RemoveScenario(std::string scenarioName){
    //delete instance from memory and remove from map
    //scenarios[scenarioName].reset();
    //scenarios.erase(scenarioName);
    throw std::runtime_error("Not implemented");
};

void Benchmark::mapScenarioToParameter(std::string scenarioName, Parameter parameter){
    scenarios[scenarioName]->parameters = parameter;
};

void Benchmark::mapScenarioToMetrics(std::string scenarioName, std::map<std::string, Metrics> metrics){
    scenarios[scenarioName]->metrics = metrics;
};

void Benchmark::RunScenario(std::string ScenarioName){
};

std::vector<std::string> RunScenariosWithParameters(std::map<std::string, Scenario> scenarios){
    throw std::runtime_error("Not implemented");
};

std::vector<std::string> Benchmark::RunScenarioUsingStrategy(std::map<std::string, Scenario>, size_t executionStrategy){
    throw std::runtime_error("Not implemented");
};