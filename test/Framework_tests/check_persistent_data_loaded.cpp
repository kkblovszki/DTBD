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
    assert(scenario->SimulatorInstance->GetSimulatorInfo().nativeOutputType == "Float"); //check that the simulator native output type is correct
    assert(scenario->SimulatorInstance->GetSimulatorInfo().supportedParameters.size() != 0); //check that the simulator has no supported parameters
    assert(scenario->SimulatorInstance->GetSimulatorInfo().supportedMetrics.size() != 0);
    assert(scenario->SimulatorInstance->GetSimulatorInfo().supportedBuildOptions.size() != 0); // check that the simulator has some supported build options

    std::cout << "---------- Parameters ----------" << std::endl;
    //print the supported parameters
    for (auto parameter : scenario->SimulatorInstance->GetSimulatorInfo().supportedParameters){
        std::cout << "Parameter: " << parameter << std::endl;
    }

    std::cout << "---------- Metrics ----------" << std::endl;
    //print the supported metrics
    for(auto metric : scenario->SimulatorInstance->GetSimulatorInfo().supportedMetrics){
        std::cout << "Metric: " << metric << std::endl;
    }

    std::cout << "---------- Build Options ----------" << std::endl;
    //print the supported build options
    for(auto buildOption : scenario->SimulatorInstance->GetSimulatorInfo().supportedBuildOptions){
        std::cout << "Build option: " << buildOption << std::endl;
    }


    return 0;
}

