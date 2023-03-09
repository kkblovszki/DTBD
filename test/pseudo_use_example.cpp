#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <functional>
#include "yaml-cpp/yaml.h"

typedef struct metric{
    std::string name;
    std::string unit;
}metric;

typedef struct parameter{
    std::string name;
    std::string value;
};

class Testbed{
    public:
    Testbed() = default;
    ~Testbed() = default;
    void CreateBenchmark(std::string name, std::string description);

    
    
    std::map<std::string, std::unique_ptr<Benchmark>> benchmarks;
};  

class Benchmark {
    public:
        Benchmark() = default;
        ~Benchmark() = default;

        void LoadConfig(std::string path){
            YAML::Node config = YAML::LoadFile(path);
            std::vector<parameter> parameters = {};
            for (YAML::const_iterator it = config.begin(); it != config.end(); ++it) {
                parameter parameter;
                parameter.name = it->first.as<std::string>();
                parameter.value = it->second.as<std::string>();
                parameters.push_back(parameter);
            }
        }

        void CreateScenario(std::string name, std::string description){
            scenarios[name] = std::make_unique<Scenario>(name, description);
        }

        void mapMetricsToScenario(std::string scenarioName, std::vector<metric> metrics){    
            scenarios[scenarioName]->metrics = metrics;
        }
        
        void mapParametersToScenario(std::string scenarioName, std::vector<parameter> parameters){
            scenarios[scenarioName]->parameters[parameter.name] = parameter.value;
        }

        std::map<std::string, std::unique_ptr<Scenario>> scenarios;
    
    private:
        std::vector<std::map<std::string, metric>> metrics;
        std::vector<std::map<std::string, parameter>> parameters;
};

class Scenario {
    public:
        Scenario(const std::string& scenarioName, const std::string& scenarioDescription) : name(name), description(scenarioDescription) {};
        ~Scenario() = default;

    private:
        std::string name;
        std::string description;
        std::vector<metric> metrics;
        std::vector<parameter> parameters;
};


int main() {

    std::unique_ptr<Testbed> testbed = std::make_unique<Testbed>();
    
    testbed->CreateBenchmark("Benchmark_NS3", "new_benchmark_description");

    testbed->LoadConfig("NS3config.yaml");
    
    //Scenario 1
    testbed->benchmarks["Benchmark_NS3"]->createScenario("Scenario_1", "new_scenario_description");    
    testbed->mapParametersToScenario("Benchmark_1", "Scenario_1", parameters[0]);
    testbed->mapMetricsToScenario("Benchmark_1", "Scenario_1", metrics[0]);

    //Scenario 2
    testbed->benchmarks["Benchmark_NS3"]->createScenario("Scenario_2", "new_scenario_description");
    testbed->mapParametersToScenario("Benchmark_1", "Scenario_2", parameters[1]);
    testbed->mapMetricsToScenario("Benchmark_1", "Scenario_2", metrics[1]);
    
    //get ouput from scenario_2 using the observer pattern
    testbed->benchmarks["Benchmark_NS3"]->scenarios["Scenario_2"]->getOutput();

    //get simulatorinfo from simulator
    testbed->benchmarks["Benchmark_NS3"]->scenarios["Scenario_2"]->getSimulatorInfo();
 
    return 0;
}