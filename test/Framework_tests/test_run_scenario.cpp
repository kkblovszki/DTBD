#include <iostream>
#include <cassert>
#include <core.Testbed.hpp>

// Description: Test the running of a scenario.

int main(){

    //create testbed
    Testbed testbed;

    std::cout << "Testbed created" << std::endl;

    testbed.CreateBenchmark("testBenchmark"); // Create a benchmark

    std::cout << "Benchmark created" << std::endl;

    testbed.benchmarks["testBenchmark"]->CreateScenario("testScenario"); // Create a scenario

    std::cout << "Scenario created" << std::endl;

    //load the config file (only testable when parser is implemented properly)
    //testbed.benchmarks["testBenchmark"]->LoadBenchmarkConfig("DTDB/test/Framework_tests/load_sim_config_desc.yam");

    //Run the scenario
    testbed.benchmarks["testBenchmark"]->RunScenario("testScenario"); 

    std::cout << "Scenario ran" << std::endl;

};