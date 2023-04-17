#include <iostream>
#include <core.Testbed.hpp>

int main(int argc, char** argv) {
    Testbed testbed;

    const std::string configPath = "test/Framework_tests/load_sim_config_desc.yaml";
    
    testbed.CreateBenchmark("testBenchmark"); // Create a benchmark

    testbed.LoadBenchmarkConfig("testBenchmark", configPath); // Load the config file

    return 0;
}