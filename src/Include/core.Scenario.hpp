#ifndef SCENARIO_HPP
#define SCENARIO_HPP

#include "core.Types.hpp"
#include "SimulatorCreator.hpp"
#include "ListenerCreator.hpp"
#include "SimulatorMockUpInterface.hpp"
#include "AbstractListener.hpp"

/**
 * \page ScenarioPage Scenario
 *
 * This is the Scenario page. It documents the Scenario class.
 */

/**
 * \brief Scenario documentation.
 *
 * This is the Scenario class. It does some things and has some properties.
 * For more information, see \ref Scenario.
 */
class Scenario{
public:
    const std::string scenarioName;
    std::vector<Metrics> metrics;
    std::vector<Parameter> parameters;
    std::unique_ptr<SimulatorMockUpInterface> SimulatorInstance;

    Scenario(std::string uniqueName, std::string& simulatorType, const std::string& simulatorVersion = "", const std::string& listenerType = "ConsoleListener");
    Scenario(std::string uniqueName, std::string& simulatorType, const std::string& simulatorVersion = "", const std::vector<BuildOptions>& buildOptions = {}, const std::string& listenerType = "ConsoleListener");
    ~Scenario();

    //void PrepareSimulation();
    void PrepareSimulation(const std::vector<Metrics>& metrics = {}, const std::vector<Parameter>& parameters = {});
    
};

#endif