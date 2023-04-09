#include <iostream>
#include <core.Testbed.hpp>

#define DEBUG

int main(int argc, char** argv) {
    Testbed testbed;
    
    testbed.CreateBenchmark("testBenchmark"); // Create a benchmark

    testbed.LoadBenchmarkConfig("testBenchmark", "test/Framework_tests/load_sim_config_desc.yaml"); // Load the config file

    return 0;
}