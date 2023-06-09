#include <iostream>
#include <filesystem>
#include <source_location>
#include <core.Testbed.hpp>

int main(){
    Testbed testbed;

    namespace fs = std::filesystem;

    const std::source_location& loc = std::source_location::current(); 

    fs::path SourcePath = loc.file_name();

    fs::path configFile = SourcePath.parent_path() / "exec_order_config.yaml";
    
    std::cout << "SourcePath: " << SourcePath << std::endl;
    std::cout << "configFile: " << configFile << std::endl;

    testbed.CreateBenchmark("P2P_Benchmark");

    testbed.LoadBenchmarkConfig("P2P_Benchmark", configFile.string());

    std::cout << "----------- Benchmarks -----------" << std::endl;
    std::vector<std::string> benchmarks = testbed.ListBenchmarks(true);

    std::cout << "-----------------------------------" << std::endl;

    testbed.benchmarks["P2P_Benchmark"]->CreateScenario("p2p-2-node-network");
    testbed.benchmarks["P2P_Benchmark"]->CreateScenario("p2p-scalable-network");

    testbed.benchmarks["P2P_Benchmark"]->RunScenariosUsingStrategy();
}