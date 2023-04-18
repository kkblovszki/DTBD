#include <gtest/gtest.h>
#include <parser.hpp>
#include <yaml-cpp/yaml.h>

// Test parseScenario
TEST(ParserTest, parseScenarioTest) {
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

    EXPECT_EQ(scenario.name, "TestScenario");
    EXPECT_EQ(scenario.description, "This is a test scenario");
    EXPECT_EQ(scenario.simulator, "TestSimulator");
    EXPECT_EQ(scenario.optional.size(), 2);
    EXPECT_EQ(scenario.optional.at("opt1"), "value1");
    EXPECT_EQ(scenario.optional.at("opt2"), "value2");
    EXPECT_EQ(scenario.required.size(), 3);
    EXPECT_EQ(scenario.required.at("param1"), "value1");
    EXPECT_EQ(scenario.required.at("param2"), "value2");
    EXPECT_EQ(scenario.required.at("param3"), "value3");
    EXPECT_EQ(scenario.parameters.size(), 2);
    EXPECT_EQ(scenario.parameters[0].name, "parameter1");
    EXPECT_EQ(scenario.parameters[0].defaultParameter, std::to_string(10));
    EXPECT_EQ(scenario.parameters[1].name, "parameter2");
    EXPECT_EQ(scenario.parameters[1].defaultParameter, std::to_string(20));
    EXPECT_EQ(scenario.buildOptions.size(), 2);
    EXPECT_EQ(scenario.buildOptions[0].buildOption, "option1");
    EXPECT_EQ(scenario.buildOptions[0].buildOptionValue, "value1");
    EXPECT_EQ(scenario.buildOptions[1].buildOption, "option2");
    EXPECT_EQ(scenario.buildOptions[1].buildOptionValue, "value2");
}

// Test parseSimulationStrategy
TEST(ParserTest, parseSimulationStrategyTest) {
    YAML::Node simulationStrategyNode = YAML::Load("{multithread: true, thread_nr: 8, ExecutionOrder: {1: setup, 2: simulate, 3: analyze}}");

    SimulationStrategy simulationStrategy;
    Parser::parseSimulationStrategy(simulationStrategyNode, simulationStrategy);

    EXPECT_EQ(simulationStrategy.multithread, true);
    EXPECT_EQ(simulationStrategy.threadNr, 8);
    EXPECT_EQ(simulationStrategy.executionOrder.size(), 3);
    EXPECT_EQ(simulationStrategy.executionOrder[1], "setup");
    EXPECT_EQ(simulationStrategy.executionOrder[2], "simulate");
    EXPECT_EQ(simulationStrategy.executionOrder[3], "analyze");
}

// Test parseBenchmark
TEST(ParserTest, parseBenchmarkTest) {
    YAML::Node benchmarkNode = YAML::Load("{SimulationStrategy: {multithread: true, thread_nr: 8, ExecutionOrder: {1: setup, 2: simulate, 3: analyze}}}");

    std::map<std::string, ScenarioDescriptor> ScenarioDescriptors;
    SimulationStrategy simulationStrategy;
    Parser::parseBenchmark(benchmarkNode, ScenarioDescriptors, simulationStrategy);

    EXPECT_EQ(ScenarioDescriptors.size(), 0);
    EXPECT_EQ(simulationStrategy.multithread, true);
    EXPECT_EQ(simulationStrategy.threadNr, 8);
    EXPECT_EQ(simulationStrategy.executionOrder.size(), 3);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
