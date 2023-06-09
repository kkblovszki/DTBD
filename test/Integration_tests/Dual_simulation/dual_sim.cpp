#include <iostream>
#include <filesystem>
#include <source_location>
#include <core.Testbed.hpp>

int main(){
    Testbed testbed;

    namespace fs = std::filesystem;

    const std::source_location& loc = std::source_location::current(); 

    fs::path SourcePath = loc.file_name();

    fs::path configFile = SourcePath.parent_path() / "dual_config.yaml";
    
    std::cout << "SourcePath: " << SourcePath << std::endl;
    std::cout << "configFile: " << configFile << std::endl;

    testbed.CreateBenchmark("P2P_Benchmark");

    testbed.LoadBenchmarkConfig("P2P_Benchmark", configFile.string());

    std::cout << "----------- Benchmarks -----------" << std::endl;

    std::vector<std::string> benchmarks = testbed.ListBenchmarks(true);

    std::cout << "----------- Scenario Descriptor: p2p-2-node-network -----------" << std::endl;

    std::cout << "Scenario Name: " << testbed.benchmarks["P2P_Benchmark"]->scenariosDescriptors["p2p-2-node-network"].name << std::endl;
    
    std::cout << "Description: " <<  testbed.benchmarks["P2P_Benchmark"]->scenariosDescriptors["p2p-2-node-network"].description << std::endl;

    std::vector<Parameter> params1 = testbed.benchmarks["P2P_Benchmark"]->scenariosDescriptors["p2p-2-node-network"].parameters;

    std::cout << "Parameters Size:" << testbed.benchmarks["P2P_Benchmark"]->scenariosDescriptors["p2p-2-node-network"].parameters.size() << std::endl; 

    for(auto& param : params1){
        std::cout << "Parameter name: " << param.name << " - Value: " << param.defaultParameter << std::endl;
    }

    std::cout << "----------- Scenario Descriptor: p2p-timed-network -----------" << std::endl;

    std::cout << "Scenario Name: " << testbed.benchmarks["P2P_Benchmark"]->scenariosDescriptors["p2p-timed-network"].name << std::endl;
    
    std::cout << "Description: " <<  testbed.benchmarks["P2P_Benchmark"]->scenariosDescriptors["p2p-timed-network"].description << std::endl;

    std::vector<Parameter> params2 = testbed.benchmarks["P2P_Benchmark"]->scenariosDescriptors["p2p-timed-network"].parameters;

    std::cout << "Parameters Size:" << testbed.benchmarks["P2P_Benchmark"]->scenariosDescriptors["p2p-timed-network"].parameters.size() << std::endl; 

    for(auto& param : params2){
        std::cout << "Parameter name: " << param.name << " - Value: " << param.defaultParameter << std::endl;
    }

    testbed.benchmarks["P2P_Benchmark"]->CreateScenario("p2p-2-node-network");
    testbed.benchmarks["P2P_Benchmark"]->CreateScenario("p2p-timed-network");

    testbed.benchmarks["P2P_Benchmark"]->RunScenarioWithParameters("p2p-2-node-network");

    testbed.benchmarks["P2P_Benchmark"]->RunScenarioWithParameters("p2p-timed-network");
}