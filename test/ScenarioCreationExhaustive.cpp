#include <iostream>
#include <cassert>

#include "../src/Include/core.Scenario.hpp"


//main function which creates scenario and performs exhaustive testing on it
int main() {

    std::unique_ptr<Scenario> singleScenario = std::make_unique<Scenario>("testScenario", "NS3", "TestListener");

    std::cout << "Scenario Exist: ";
    assert(singleScenario != nullptr);
    std::cout << "True" << std::endl;
    
    std::cout << "Asserting scenario name: ";
    assert(singleScenario->scenarioName == "testScenario"); 
    std::cout << "True - " << singleScenario->scenarioName << std::endl;

    std::cout << "Asserting simulator existing: ";
    assert(singleScenario->Simulator != nullptr);
    std::cout << "True" << std::endl;

    std::cout << "Asserting simulator name: ";
    assert(singleScenario->Simulator->simulator.simulatorName == "NS3");
    std::cout << "True - " << singleScenario->Simulator->simulator.simulatorName << std::endl;

    std::cout << "Asserting simulator version: ";
    assert(singleScenario->Simulator->simulator.simulatorVersion == "3.29");
    std::cout << "True - " << singleScenario->Simulator->simulator.simulatorVersion << std::endl;

    std::cout << "Asserting simulator type: ";
    assert(singleScenario->Simulator->simulator.nativeOutputType == "ns3::Packet");
    std::cout << "True - " << singleScenario->Simulator->simulator.simulatorVersion << std::endl;

    std::cout << "Asserting listener existing: ";
    assert(singleScenario->activeSimulatorListener != nullptr);
    std::cout << "True" << std::endl;


    std::cout << "Framework scenario creation: success" << std::endl;

    return 0;
}

