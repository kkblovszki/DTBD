#include <iostream>
#include "Include/core.Testbed.hpp"
#include <cassert>


int main() {

    //Testbed testbed = Testbed();

    std::unique_ptr<Scenario> singleScenario = std::make_unique<Scenario>("testScenario", "NS3", "TESTLISTENER");

    std::cout << "Scenario Exist: ";
    assert(singleScenario != nullptr);
    std::cout << "True" << std::endl;
    
    std::cout << "Asserting scenario name: ";
    assert(singleScenario->scenarioName == "testScenario"); 
    std::cout << "True" << std::endl;

    std::cout << "Asserting simulator existing: ";
    assert(singleScenario->Simulator != nullptr);
    std::cout << "True" << std::endl;

    //std::cout << "Asserting simulator name: ";
    //assert(singleScenario->Simulator->simulator.simulatorName == "NS3");
    //std::cout << "True" << std::endl;

    std::cout << "Framework scenario creation: success" << std::endl;
    
    return 0;
}
