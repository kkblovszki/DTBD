#include <Parser.hpp>
#include <yaml-cpp/yaml.h>
#include <cassert>
#include <filesystem>
#include <source_location>

int main() {
    //Get filepath of YAML file
    namespace fs = std::filesystem;
    const std::source_location& loc = std::source_location::current(); 
    fs::path SourcePath = loc.file_name();
    fs::path configFile = SourcePath.parent_path() / "test.yaml";

    std::cout << "SourcePath: " << SourcePath << std::endl;
    std::cout << "configFile: " << configFile << std::endl;

    //Test parseScenario
    //YAML::Node scenarioNode = YAML::Load("{name: TestScenario, description: This is a test scenario, simulator: TestSimulator, optional: {opt1: value1, opt2: value2}, required: {param1: value1, param2: value2, param3: value3}, Parameters: {parameter1: 10, parameter2: 20}, BuildOptions: {option1: value1, option2: value2}}");
    //YAML::Node scenarioNode = YAML::Load(yaml_string);
    YAML::Node scenarioNode = YAML::LoadFile(configFile);
    ScenarioDescriptor scenario;
    Parser::parseScenario(scenarioNode, scenario);

    assert(scenario.name == "TestScenario");
    std::cout << scenario.name << std::endl;
    assert(scenario.description == "This is a test scenario");
    std::cout << scenario.description << std::endl;
    assert(scenario.simulator == "TestSimulator");
    std::cout << scenario.simulator << std::endl;
    assert(scenario.optional.size() == 2);
    std::cout << scenario.optional.size() << std::endl;
    assert(scenario.optional.at("opt1") == "value1");
    std::cout << scenario.optional.at("opt1") << std::endl;
    assert(scenario.optional.at("opt2") == "value2");
    std::cout << scenario.optional.at("opt2") << std::endl;
    assert(scenario.required.size() == 3);
    std::cout << scenario.required.size() << std::endl;
    assert(scenario.required.at("param1") == "value1");
    std::cout << scenario.required.at("param1") << std::endl;
    assert(scenario.required.at("param2") == "value2");
    std::cout << scenario.required.at("param2") << std::endl;
    assert(scenario.required.at("param3") == "value3");
    std::cout << scenario.required.at("param3") << std::endl;
    assert(scenario.parameters.size() == 2);
    std::cout << scenario.parameters.size() << std::endl;
    assert(scenario.parameters[0].name == "parameter1");
    std::cout << scenario.parameters[0].name << std::endl;
    assert(scenario.parameters[0].defaultParameter == std::to_string(10));
    std::cout << scenario.parameters[0].defaultParameter << std::endl;
    assert(scenario.parameters[1].name == "parameter2");
    std::cout << scenario.parameters[1].name << std::endl;
    assert(scenario.parameters[1].defaultParameter == std::to_string(20));
    std::cout << scenario.parameters[1].defaultParameter << std::endl;
    assert(scenario.buildOptions.size() == 2);
    std::cout << scenario.buildOptions.size() << std::endl;
    assert(scenario.buildOptions[0].buildOption == "option1");
    std::cout << scenario.buildOptions[0].buildOption << std::endl;
    assert(scenario.buildOptions[0].buildOptionValue == "value1");
    std::cout << scenario.buildOptions[0].buildOptionValue << std::endl;
    assert(scenario.buildOptions[1].buildOption == "option2");
    std::cout << scenario.buildOptions[1].buildOption << std::endl;
    assert(scenario.buildOptions[1].buildOptionValue == "value2");
    std::cout << scenario.buildOptions[1].buildOptionValue << std::endl;

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
