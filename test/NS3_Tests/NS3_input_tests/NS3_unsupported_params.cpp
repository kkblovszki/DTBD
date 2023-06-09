#include <iostream>
#include <filesystem>
#include <source_location>

#include <core.Testbed.hpp>

//! This test is supposed to fail because of unsupported parameters in the NS3 input file
int main(){
    Testbed testbed;

    namespace fs = std::filesystem;

    const std::source_location& loc = std::source_location::current(); 

    fs::path SourcePath = loc.file_name();

    fs::path configFile = SourcePath.parent_path() / "Unsupported_Config_params.yaml";
    
    std::cout << "SourcePath: " << SourcePath << std::endl;
    std::cout << "configFile: " << configFile << std::endl;

    testbed.CreateBenchmark("UnsupportedParametersBenchmark");

    testbed.LoadBenchmarkConfig("UnsupportedParametersBenchmark", configFile.string());

    testbed.benchmarks["UnsupportedParametersBenchmark"]->CreateScenario("NS3_unsupported_config_params_test");

    testbed.benchmarks["UnsupportedParametersBenchmark"]->RunScenarioWithParameters("NS3_unsupported_config_params_test");
}
