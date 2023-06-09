#include <iostream>
#include <filesystem>
#include <source_location>

#include <core.Testbed.hpp>

int main(){
    Testbed testbed;

    namespace fs = std::filesystem;

    const std::source_location& loc = std::source_location::current(); 

    fs::path SourcePath = loc.file_name();

    fs::path configFile = SourcePath.parent_path() / "single_config.yaml";

    testbed.CreateBenchmark("single_scenario_simulation");

    testbed.LoadBenchmarkConfig("single_scenario_simulation", configFile.string());

    testbed.benchmarks["single_scenario_simulation"]->CreateScenario("single_simulation");

    testbed.benchmarks["single_scenario_simulation"]->RunScenarioWithParameters("single_simulation");
}