#ifndef CORE_TYPES_HPP
#define CORE_TYPES_HPP

#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <memory>
#include <functional>


/**
 * @brief
 * 
 */
typedef struct BuildOptions {
        std::string buildOption;
        std::string buildOptionValue;
} BuildOptions;


/**
 * @brief 
 * 
 */
typedef struct Parameter {
    std::string name;
    std::string defaultParameter;
} Parameter;


/**
 * @brief 
 * The descriptor of the scenario structure.
 */
typedef struct ScenarioDescriptor {
    std::string name;
    std::string description;
    std::string simulator;
    std::string listener;
    std::map<std::string, std::string> optional;
    std::map<std::string, std::string> required;
    std::vector<Parameter> parameters;
    std::vector<BuildOptions> buildOptions;
}ScenarioDescriptor;

/**
 * @brief 
 * 
 */
typedef struct SimulationStrategy {
    bool multithread;
    int threadNr;
    std::map<int, std::string> executionOrder;
}SimulationStrategy;

/**
 * @brief 
 * 
 */
struct BenchmarkType{
    SimulationStrategy simulationStrategy;
    std::vector<ScenarioDescriptor> scenarios;
};

/**
 * @brief
 * 
 */
typedef struct Metrics {
    std::string name;
    std::string unit;

    Metrics(){name = "NULL"; unit = "NULL";};
    Metrics(std::string specifiedName, std::string specifiedUnit) : name(specifiedName), unit(specifiedUnit){};
    ~Metrics(){};
} Metrics;

/**
 * @brief 
 * 
 */
typedef struct Measure {
    Metrics metric;
    std::string label;
    std::map<Metrics, std::vector<std::string>> readings;
    //std::vector<std::string> readings;

    Measure(Metrics specifiedMetric, 
            std::string specifiedLabel, 
            std::map<Metrics, std::vector<std::string>> specifiedReadings) 
            : metric(specifiedMetric), 
            label(specifiedLabel), 
            readings(specifiedReadings){};
    Measure(){};
} Measure;

/**
 * @brief 
 * 
 */
typedef struct SimulatorInfo {
    std::string simulatorName;
    std::string simulatorVersion;
    std::string nativeOutputType;
    std::vector<std::string> functions;
    std::vector<std::string> supportedParameters;
    std::vector<std::string> supportedMetrics;
    
    SimulatorInfo(const std::string& simulatorName  = "", 
                const std::string& simulatorVersion = "", 
                const std::string& nativeOutputType = "", 
                const std::vector<std::string>& functions   = {}, 
                const std::vector<std::string>& parameters  = {}) 
                : simulatorName(simulatorName), 
                simulatorVersion(simulatorVersion), 
                nativeOutputType(nativeOutputType), 
                functions(functions), 
                supportedParameters(parameters){}
} SimulatorInfo;

#endif



