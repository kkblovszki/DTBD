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
        
        void mapMetricsToScenario(std::string benchmarkName, std::string scenarioName, std::vector<metric> metrics){    
                benchmarks[benchmarkName]->scenarios[scenarioName]->metrics = ;
        }
        
        void mapParametersToScenario(std::string benchmarkName, std::string scenarioName, std::vector<parameter> parameters){
            benchmarks[benchmarkName]->scenarios[scenarioName]->parameters[parameter.name] = parameter.value;
        }

        std::map<std::string, std::unique_ptr<Benchmark>> benchmarks;

        private:
        std::map<std::shared_ptr<metric>> metrics;
        std::vector<std::shared_ptr<parameter>> parameters;
};  

class Benchmark {
    public:
        Benchmark() = default;
        ~Benchmark() = default;

        void CreateScenario(std::string name, std::string description){
            scenarios[name] = std::make_unique<Scenario>(name, description);
        }
        
        std::map<std::string, std::unique_ptr<Scenario>> scenarios;
        
    private:
};

class Scenario {
    public:
        Scenario(const std::string& scenarioName, const std::string& scenarioDescription) : name(name), description(scenarioDescription) {};
        ~Scenario() = default;

        void CreateMetric(std::string name, std::string description);
        void CreateMetric(metric metric);
        void CreateMetric(std::vector<metric> metrics);

    private:
        std::string name;
        std::string description;
        std::vector<metric> metrics;
};


int main() {

    std::vector<metric> metrics = {};
        
    std::unique_ptr<Testbed> testbed = std::make_unique<Testbed>();
    
    testbed->CreateBenchmark("Benchmark_1", "new_benchmark_description");

    testbed->benchmarks["Benchmark_1"]->createScenario("Scenario_1", "new_scenario_description");

    //loads config from yaml file and parses the parameters to the defined scenario
    
    

    testbed->mapParametersToScenario("Benchmark_1", "Scenario_1", parameters);
    testbed->mapMetricsToScenario("Benchmark_1", "Scenario_1", metrics);

    return 0;
}