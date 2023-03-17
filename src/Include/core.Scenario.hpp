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
 * This is the MyClass class. It does some things and has some properties.
 *
 * For more information, see \ref Scenario.
 */
class Scenario {
public:
    const std::string scenarioName;
    std::map<std::string, Metrics> metrics;
    Parameter parameters; 
    std::unique_ptr<SimulatorMockUpInterface> Simulator;
    //std::unique_ptr<Listener> activeSimulatorListener;

    //Scenario(): scenarioName(NULL){metrics = {}; parameters.name = 'NULL'; parameters.defaultParameter = 0; parameters.underTest = NULL;};
    Scenario(std::string uniqueName, std::string simulatorType, std::string ListenerType);
    ~Scenario();

    void PrepareSimulation(std::map<std::string, size_t> Strategy);
};