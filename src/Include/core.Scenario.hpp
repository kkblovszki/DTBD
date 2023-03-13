#include "core.Types.hpp"
#include "SimulatorCreator.hpp"
#include "ListenerCreator.hpp"
#include "SimulatorMockUpInterface.hpp"
#include "AbstractListener.hpp"

class Scenario {
public:
    const std::string scenarioName;
    std::map<std::string, Metrics> metrics;
    Parameter parameters; 
    //Scenario(): scenarioName(NULL){metrics = {}; parameters.name = 'NULL'; parameters.defaultParameter = 0; parameters.underTest = NULL;};
    Scenario(std::string uniqueName, std::string simulatorType, std::string ListenerType);

    ~Scenario();
    

    void PrepareSimulation(std::map<std::string, size_t> Strategy);
};