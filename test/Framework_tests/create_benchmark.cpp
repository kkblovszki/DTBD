#include <iostream>
#include <cassert>
#include <filesystem>
#include <source_location>
#include <core.Testbed.hpp>

int main(int argc, char** argv) {
    Testbed testbed;

    namespace fs = std::filesystem;

    const std::source_location& loc = std::source_location::current(); 

    fs::path SourcePath = loc.file_name();

    fs::path configFile = SourcePath.parent_path() / "load_sim_config_desc.yaml";
    
    testbed.CreateBenchmark("testBenchmark");

    testbed.LoadBenchmarkConfig("testBenchmark", configFile);

    testbed.benchmarks["testBenchmark"]->CreateScenario("TutorialScenario");

    std::cout << "Benchmark & Scenario created" << std::endl;

    return 0;
}