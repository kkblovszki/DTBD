#include "core.Types.hpp"
#include "SimulatorMockUpInterface.hpp"
#include "core.Scenario.hpp"


//! Benchmark class
/*!
    This class is responsible for managing the simulation scenarios.
    It is responsible for creating, removing, and running scenarios.
*/
class Benchmark {
private:
    std::map<std::string, std::unique_ptr<Scenario>> scenarios;

public:
    Benchmark(){};
    ~Benchmark(){};

    void LoadSimulationConfig(std::string configPath){
        // load yaml config file
    };

    void CreateScenario(std::string scenarioName){
        //scenarios[scenarioName] = std::make_unique<Scenario>(scenarioName, "NS3", "DefaultListener");
    };

    void RemoveScenario(std::string scenarioName){
        //delete instance from memory and remove from map
        //scenarios[scenarioName].reset();
        //scenarios.erase(scenarioName);
    };

    void mapScenarioToParameter(std::string scenarioName, Parameter parameter){
        scenarios[scenarioName]->parameters = parameter;
    };

    void mapScenarioToMetrics(std::string scenarioName, std::map<std::string, Metrics> metrics){
        scenarios[scenarioName]->metrics = metrics;
    };

    void RunScenario(std::string ScenarioName){};
    std::vector<std::string> RunScenariosWithParameters(std::map<std::string, Scenario> scenarios){
        throw std::runtime_error("Not implemented");
    };
    std::vector<std::string> RunScenarioUsingStrategy(std::map<std::string, Scenario>, size_t executionStrategy){
        throw std::runtime_error("Not implemented");
    };
};


