#include <parser.hpp>
#include <yaml-cpp/yaml.h>
#include <cassert>

int main() {
    //Test parseScenario
    std::string yaml_string = R"(
        name: TestScenario
        description: This is a test scenario
        simulator: TestSimulator
        optional:
        - opt1: value1
        - opt2: value2
        required:
        - param1: value1
        - param2: value2
        - param3: value3
        parameters:
        - name: parameter1
          defaultParameter: 10
        - name: parameter2
          defaultParameter: 20
        buildOptions:
        - buildOption: option1
          buildOptionValue: value1
        - buildOption: option2
          buildOptionValue: value2
    )";
    //YAML::Node scenarioNode = YAML::Load("{name: TestScenario, description: This is a test scenario, simulator: TestSimulator, optional: {opt1: value1, opt2: value2}, required: {param1: value1, param2: value2, param3: value3}, Parameters: {parameter1: 10, parameter2: 20}, BuildOptions: {option1: value1, option2: value2}}");
    //YAML::Node scenarioNode = YAML::Load(yaml_string);
    YAML::Node scenarioNode = YAML::LoadFile("test.yaml");
    ScenarioDescriptor scenario;
    Parser::parseScenario(scenarioNode, scenario);

    assert(scenario.name == "TestScenario");
    assert(scenario.description == "This is a test scenario");
    assert(scenario.simulator == "TestSimulator");
    assert(scenario.optional.size() == 2);
    assert(scenario.optional.at("opt1") == "value1");
    assert(scenario.optional.at("opt2") == "value2");
    assert(scenario.required.size() == 3);
    assert(scenario.required.at("param1") == "value1");
    assert(scenario.required.at("param2") == "value2");
    assert(scenario.required.at("param3") == "value3");
    assert(scenario.parameters.size() == 2);
    assert(scenario.parameters[0].name == "parameter1");
    assert(scenario.parameters[0].defaultParameter == std::to_string(10));
    assert(scenario.parameters[1].name == "parameter2");
    assert(scenario.parameters[1].defaultParameter == std::to_string(20));
    assert(scenario.buildOptions.size() == 2);
    assert(scenario.buildOptions[0].buildOption == "option1");
    assert(scenario.buildOptions[0].buildOptionValue == "value1");
    assert(scenario.buildOptions[1].buildOption == "option2");
    assert(scenario.buildOptions[1].buildOptionValue == "value2");

    //Test parseSimulationStrategy
    YAML::Node simulationStrategyNode = YAML::Load("{multithread: true, thread_nr: 8, ExecutionOrder: {1: setup, 2: simulate, 3: analyze}}");
    SimulationStrategy simulationStrategy;
    Parser::parseSimulationStrategy(simulationStrategyNode, simulationStrategy);

    assert(simulationStrategy.multithread == true);
    assert(simulationStrategy.threadNr == 8);
    assert(simulationStrategy.executionOrder.size() == 3);
    assert(simulationStrategy.executionOrder[1] == "setup");
    assert(simulationStrategy.executionOrder[2] == "simulate");
    assert(simulationStrategy.executionOrder[3] == "analyze");

    //Test parseBenchmark
    YAML::Node benchmarkNode = YAML::Load("{SimulationStrategy: {multithread: true, thread_nr: 8, ExecutionOrder: {1: setup, 2: simulate, 3: analyze}}}");
    std::map<std::string, ScenarioDescriptor> ScenarioDescriptors;
    Parser::parseBenchmark(benchmarkNode, ScenarioDescriptors, simulationStrategy);
    
    assert(ScenarioDescriptors.size() == 0);
    assert(simulationStrategy.multithread == true);
    assert(simulationStrategy.threadNr == 8);
    assert(simulationStrategy.executionOrder.size() == 3);
    
    return 0;
}
