#include "include/core.Types.hpp"
#include "include/SimulatorCreator.hpp"
#include "include/SimulatorMockUpInterface.hpp"


class Benchmark {
private:
    std::map<std::string, Scenario> scenarios;

public:
    Benchmark();
    ~Benchmark();

    void CreateBenchmark(Scenario scenarios){};
    Scenario RunScenario(){};
    std::vector<std::string> RunScenariosWithParameters(std::map<std::string, Scenario> scenarios){};
    std::vector<std::string> RunScenarioUsingStrategy(std::map<std::string, Scenario>, size_t executionStrategy){};
};

Benchmark::Benchmark(){}
Benchmark::~Benchmark(){}



class Scenario {
private:
    const std::string scenarioName;
    std::map<std::string, Metrics> metrics;
    Parameter parameters; 

public:
    //Scenario(): scenarioName(NULL){metrics = {}; parameters.name = 'NULL'; parameters.defaultParameter = 0; parameters.underTest = NULL;};
    ~Scenario();
    Scenario(std::string scenarioName, std::string simulatorType);

    void PrepareExecution(std::map<std::string, size_t> Strategy);
};

Scenario::~Scenario() {}

Scenario::Scenario(std::string uniqueName, std::string simulatorType) : scenarioName(uniqueName) {
    std::unique_ptr<Listener> newListener = std::make_unique<Listener>();

    // create new simulator instance 
    SimulatorCreator::CreateSimulator(simulatorType);


    // connect that listener to the simulator active listener
    SimulatorMockUpInterface::SetListener()
}




typedef struct Parameter {
    std::string name;
    size_t defaultParameter;
    // UML diagram says type <V> for the Parameter struct, as well as the type for the variable undertest, yet we don't know exactly what we means by this 
    size_t underTest; 

} Parameter;


