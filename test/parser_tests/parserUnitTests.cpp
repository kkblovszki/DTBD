#include <yaml-cpp/yaml.h>
#include <cassert>
#include <filesystem>
#include <source_location>

#include <Parser.hpp>

int main() {
    //Get filepath of YAML file
    namespace fs = std::filesystem;
    const std::source_location& loc = std::source_location::current(); 
    fs::path SourcePath = loc.file_name();
    fs::path configFile = SourcePath.parent_path() / "test.yaml";

    std::cout << "SourcePath: " << SourcePath << std::endl;
    std::cout << "configFile: " << configFile << std::endl;

    //Test parseBenchmark
    YAML::Node benchmarkNode = YAML::LoadFile(configFile);

    std::map<std::string, ScenarioDescriptor> scenarios;
    SimulationStrategy simulationStrategy = {0, 0, {}};

    benchmarkNode = benchmarkNode["Benchmark"]; 

    Parser::parseBenchmark(benchmarkNode,  scenarios, simulationStrategy);
    
    std::cout << "--------------- NS3 ----------------" << std::endl;
    assert(scenarios["NS3TutorialScenario"].name == "NS3 Example");
    std::cout << "NS3 Scenario name: " << scenarios["NS3TutorialScenario"].name << std::endl;
    assert(scenarios["NS3TutorialScenario"].description == "An example problem in NS3");
    std::cout << "NS3 Scenario description: " << scenarios["NS3TutorialScenario"].description << std::endl;
    assert(scenarios["NS3TutorialScenario"].simulator == "NS3");
    std::cout << "NS3 Simulator type: " << scenarios["NS3TutorialScenario"].simulator << std::endl;
    assert(scenarios["NS3TutorialScenario"].simulatorVersion == "3.38");
    std::cout << "NS3 Simulator Version: " << scenarios["NS3TutorialScenario"].simulatorVersion << std::endl;
    
    std::cout << std::endl;

    assert(scenarios["NS3TutorialScenario"].required.size() != 0);
    std::cout << "-------- NS3 Simulation Required --------" << std::endl;
    for(auto& req : scenarios["NS3TutorialScenario"].required){
        std::cout << "Name: " << req.first << " Value: " << req.second << std::endl; 
    }

    std::cout << std::endl;

    assert(scenarios["NS3TutorialScenario"].parameters.size() != 0);
    std::cout << "-------- NS3 Simulation Parameters  --------" << std::endl;
    for(auto& param : scenarios["NS3TutorialScenario"].parameters){
        std::cout << "Name: " << param.name << " Value: " << param.defaultParameter << std::endl; 
    }

    std::cout << std::endl;

    assert(scenarios["NS3TutorialScenario"].buildOptions.size() != 0);
    std::cout << "-------- NS3 Simulation BuildOptions --------" << std::endl;
    for(auto& BO : scenarios["NS3TutorialScenario"].buildOptions){
        std::cout << "Name: " << BO.buildOption << " Value: " << BO.buildOptionValue << std::endl; 
    }

    std::cout << std::endl;
    
    std::cout << "-------------- Alchemist -----------------" << std::endl;

    std::cout << "Alchemist Simulator: " << scenarios["AlchemistTutorialScenario"].name << std::endl;
    std::cout << "Alchemist Scenario description: " << scenarios["AlchemistTutorialScenario"].description << std::endl;
    std::cout << "Alchemist Simulator type: " << scenarios["AlchemistTutorialScenario"].simulator << std::endl;
    std::cout << "Alchemist Simulator Version: " << scenarios["AlchemistTutorialScenario"].simulatorVersion << std::endl;

    std::cout << std::endl;

    std::cout << "-------- Alchemist Simulation Required --------" << std::endl;
    for(auto& req : scenarios["AlchemistTutorialScenario"].parameters){
        std::cout << "Name: " << req.name << " Value: " << req.defaultParameter << std::endl; 
    }

    std::cout << std::endl;

    std::cout << "-------- Alchemist Simulation Parameters  --------" << std::endl;
    for(auto& param : scenarios["AlchemistTutorialScenario"].parameters){
        std::cout << "Name: " << param.name << " Value: " << param.defaultParameter << std::endl; 
    }

    std::cout << std::endl;
    
    return 0;
}
