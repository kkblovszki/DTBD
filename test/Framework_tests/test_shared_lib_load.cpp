
#include <iostream>
#include <cassert>
#include <core.Scenario.hpp>

// Description: Test the loading of a shared library.

int main() {

    //create a scenario which requires the ns3 simulator from the shared library and the console listener to be loaded
    std::string scenarioName = "testScenario";
    std::string simulatorType = "ns3";
    std::string simulatorVersion = "3.38";
    std::string listenerType = "ConsoleListener";

    //create a scenario which requires the ns3 simulator from the shared library and the console listener to be loaded
    std::unique_ptr<Scenario> scenario = std::make_unique<Scenario>(scenarioName, simulatorType, simulatorVersion, listenerType);

    //check if the scenario is created correctly
    assert(scenario->scenarioName == "testScenario");

    //check if the simulator is created correctly
    assert(scenario->SimulatorInstance.get() != nullptr);

    return 0;
}