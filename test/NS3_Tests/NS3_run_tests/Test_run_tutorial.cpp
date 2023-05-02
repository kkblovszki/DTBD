#include <iostream>
#include <filesystem>
#include <source_location>
#include <core.Testbed.hpp>

int main(){
    Testbed testbed;

    namespace fs = std::filesystem;

    const std::source_location& loc = std::source_location::current(); 

    fs::path SourcePath = loc.file_name();

    fs::path configFile = SourcePath.parent_path() / "Initial_basic_test.yaml";
    
    std::cout << "SourcePath: " << SourcePath << std::endl;
    std::cout << "configFile: " << configFile << std::endl;

    testbed.CreateBenchmark("TutorialBenchmark");

    testbed.LoadBenchmarkConfig("TutorialBenchmark", configFile.string());

    std::cout << "----------- Benchmarks -----------" << std::endl;
    std::vector<std::string> benchmarks = testbed.ListBenchmarks(true);

    std::cout << "----------- Scenario Descriptor -----------" << std::endl;
    std::cout << "Scenario Name: " << testbed.benchmarks["TutorialBenchmark"]->scenariosDescriptors["TutorialScenario"].name << std::endl;
    
    std::cout << "Description: " <<  testbed.benchmarks["TutorialBenchmark"]->scenariosDescriptors["TutorialScenario"].description << std::endl;

    std::vector<Parameter> params = testbed.benchmarks["TutorialBenchmark"]->scenariosDescriptors["TutorialScenario"].parameters;

    std::cout << "Parameters Size:" << testbed.benchmarks["TutorialBenchmark"]->scenariosDescriptors["TutorialScenario"].parameters.size() << std::endl; 

    for(auto& param : params){
        std::cout << "Parameter name: " << param.name << "- Value: " << param.defaultParameter << std::endl;
    }

    std::cout << "-----------------------------------" << std::endl;

    testbed.benchmarks["TutorialBenchmark"]->CreateScenario("TutorialScenario");

    //auto testbed.benchmarks["TutorialBenchmark"]->scenarios["TutorialScenario"]->SimulatorInstance->GetSimulatorInfo();
    testbed.benchmarks["TutorialBenchmark"]->RunScenarioWithParameters("TutorialScenario");
    //testbed.benchmarks["TutorialBenchmark"]->RunScenario("TutorialScenario");
}