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

    void LoadSimulationConfig(std::string configPath);

    void CreateScenario(std::string scenarioName);

    void RemoveScenario(std::string scenarioName);

    void mapScenarioToParameter(std::string scenarioName, Parameter parameter);
    void mapScenarioToMetrics(std::string scenarioName, std::map<std::string, Metrics> metrics);

    void RunScenario(std::string ScenarioName);

    std::vector<std::string> RunScenariosWithParameters(std::map<std::string, Scenario> scenarios);

    std::vector<std::string> RunScenarioUsingStrategy(std::map<std::string, Scenario>, size_t executionStrategy);

};


