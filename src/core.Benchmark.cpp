#include "include/core.Types.hpp"

class Benchmark {
private:
    std::map<std::string, Scenario> scenarios;
public:
    Benchmark(/* args */);
    ~Benchmark();
    Scenario RunScenario(){};
    std::vector<std::string> RunScenariosWithParameters(std::map<std::string, Scenario> scenarios){};
    std::vector<std::string> RunScenarioUsingStrategy(std::map<std::string, Scenario>, size_t executionStrategy){};
};

Benchmark:: Benchmark(/* args */){}
Benchmark:: ~Benchmark(){}

class Scenario {
private:
    std::string scenarioName;
    std::map<std::string, Metrics> metrics;
    Parameter parameters; 
public:
    Scenario(/* args */);
    ~Scenario();
    void PrepareExecution(std::map<std::string, size_t> Strategy){};
};

Scenario::Scenario(/* args */) {}
Scenario::~Scenario() {}

typedef struct Parameter {
    std::string name;
    size_t defaultParameter;
    // UML diagram says type <V> for the Parameter struct, as well as the type for the variable undertest, yet we don't know exactly what we means by this 
    size_t underTest; 

} Parameter;


