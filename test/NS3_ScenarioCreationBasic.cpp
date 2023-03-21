#include "../src/Include/core.Scenario.hpp"
#include <iostream>
#include <memory>
#include <cassert>

int main() {
    
    std::unique_ptr<Scenario> singleScenario = std::make_unique<Scenario>("testScenario", "NS3", "TestListener");
    
    std::cout << "Scenario Exist: ";
    assert(singleScenario != nullptr);
    std::cout << "True" << std::endl;
    
    std::cout << "Asserting scenario name: ";
    assert(singleScenario->scenarioName == "testScenario"); 
    std::cout << "True" << std::endl;

    std::cout << "Asserting simulator existing: ";
    assert(singleScenario->Simulator.get() != nullptr);
    std::cout << "True" << std::endl;

    std::cout << "Asserting single run: ";
    std::cout << "True - output: " << std::endl;
    singleScenario->Simulator->RunSimulation();
    
    std::cout << "Framework scenario creation: success" << std::endl;

    return 0;
}
