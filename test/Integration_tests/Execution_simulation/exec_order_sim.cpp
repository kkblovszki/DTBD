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

    std::cout << "-----------------------------------" << std::endl;

    testbed.benchmarks["TutorialBenchmark"]->CreateScenario("TutorialScenario1");
    testbed.benchmarks["TutorialBenchmark"]->CreateScenario("TutorialScenario2");

    testbed.benchmarks["TutorialBenchmark"]->RunScenariosUsingStrategy();
}