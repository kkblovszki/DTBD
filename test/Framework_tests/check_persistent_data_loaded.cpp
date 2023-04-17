#include <iostream>
#include <cassert>
#include <core.Scenario.hpp>

// Description: Test the Loading of the simulator configuration file.

int main(){

    //create a scenario which requires the ns3 simulator from the shared library and the console listener to be loaded
    std::string scenarioName = "testScenario";
    std::string simulatorType = "ns3";
    std::string simulatorVersion = "3.38";
    std::string listenerType = "ConsoleListener";

    //create a scenario which requires the ns3 simulator from the shared library and the console listener to be loaded
    std::unique_ptr<Scenario> scenario = std::make_unique<Scenario>(scenarioName, simulatorType, simulatorVersion, listenerType);

    //check that the scenario has been loaded correctly
    assert(scenario->SimulatorInstance->GetSimulatorInfo().simulatorName == "NS3"); //check that the simulator name is correct
    assert(scenario->SimulatorInstance->GetSimulatorInfo().simulatorVersion == "3.38"); //check that the simulator version is correct
    assert(scenario->SimulatorInstance->GetSimulatorInfo().nativeOutputType == "float"); //check that the simulator native output type is correct
    assert(scenario->SimulatorInstance->GetSimulatorInfo().supportedParameters.size() == 0); //check that the simulator has no supported parameters

    for(auto& param : scenario->SimulatorInstance->GetSimulatorInfo().supportedParameters){
        std::cout << param << std::endl;
    }

    return 0;
}

