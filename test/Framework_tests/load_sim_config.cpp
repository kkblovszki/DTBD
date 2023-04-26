#include <iostream>
#include <cassert>
#include <filesystem>
#include <core.Testbed.hpp>

int main(int argc, char** argv) {
    Testbed testbed;

    namespace fs = std::filesystem;

    std::string configPath = "/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/test/Framework_tests/load_sim_config_desc.yaml";
    
    testbed.CreateBenchmark("testBenchmark"); // Create a benchmark

    testbed.LoadBenchmarkConfig("testBenchmark", configPath); // Load the config file

    return 0;
}