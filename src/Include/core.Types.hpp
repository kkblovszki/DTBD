#ifndef CORE_TYPES_HPP
#define CORE_TYPES_HPP

#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <memory>
#include <functional>

/**
 * @brief BuildOptions structure that holds the information about a build option.
 * @param buildOption - the name of the build option
 * @param buildOptionValue - the value of the build option
 */
typedef struct BuildOptions {
        std::string buildOption;
        std::string buildOptionValue;
} BuildOptions;

/**
 * @brief Parameter structure that holds the information about a parameter.
 * @param name - the name of the parameter
 * @param defaultParameter - the default value of the parameter
 * @details This structure is used to hold the information about the parameter that is read from the simulation configuration file.
 * It is parsed to the SMI when a scenario is run, during the preparation phase.
 */
typedef struct Parameter {
    std::string name;
    std::string defaultParameter;
} Parameter;

/**
 * @brief 
 * @param name - the name of the metric
 * @param unit - the unit of the metric
 */
typedef struct Metrics {
    std::string name;
    std::string unit;

    Metrics(){name = ""; unit = "";};
    Metrics(std::string specifiedName, std::string specifiedUnit) : name(specifiedName), unit(specifiedUnit){};
    ~Metrics(){};
} Metrics;

/**
 * @brief 
 * The descriptor of the scenario structure.
 * @param name - the name of the scenario
 * @param description - the description of the scenario
 * @param simulator - the simulator that the scenario uses
 * @param simulatorVersion - the version of the simulator
 * @param listener - the listener that the scenario uses
 * @param optional - the optional parameters of the scenario
 * @param required - the required parameters of the scenario
 * @param parameters - the parameters of the scenario
 * @param metrics - the metrics of the scenario
 * @param buildOptions - the build options of the scenario
 * @details This structure is used to hold the information about the scenario that is read from the simulation configuration file.
 * The @param simulator, @param name, and @param simulatorVersion are required parameters and must be defined in the simulation configuration file.
 * to be able to create a scenario. The @param listener is an optional parameter and if it is not defined, the framework will use the default listener which is the Console Listener.
 * The @param optional and @param required are optional parameters and if they are not defined, the framework will use the default values which are empty maps. 
 * Depending on the simulator, the @param optional and @param required parameters may be used, therefore it is recommended to define them in the simulation configuration file.
 * However in the end it depends on whether the specific SMI - Simulator Mockup Interface Developer wants to use them or not, and how to use them.
 */
typedef struct ScenarioDescriptor{
    std::string name;
    std::string description;
    std::string simulator;
    std::string simulatorVersion;
    std::string listener;
    std::map<std::string, std::string> optional;
    std::map<std::string, std::string> required;
    std::vector<Parameter> parameters;
    std::vector<Metrics> metrics;
    std::vector<BuildOptions> buildOptions;

    ScenarioDescriptor() {name, description, simulator, listener = ""; 
                          optional, required = {}; 
                          parameters, metrics, buildOptions = {};}

}ScenarioDescriptor;

/**
 * @brief 
 * Structure that holds the information about the simulation strategy.
 * @param multithread - if the simulation is multithreaded
 * @param threadNr - the number of threads
 * @param executionOrder - the order of the execution of the scenarios
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
 * @brief Measure structure that holds the information about a measurement.
 * @param label - the label of the measure
 * @param readings - the readings of the measure it consist of a map of metrics and a vector of strings pr. metric
 * @details This structure is used to hold the information about the measure that is read from the simulation configuration file.
 * The Measure structure itself contains a map of multiple Metrics. The Metrics structure contains a name and a unit.
 */
typedef struct Measure {
    std::string label;
    std::map<Metrics, std::vector<std::string>> readings;

    Measure(std::string specifiedLabel, 
            std::map<Metrics, std::vector<std::string>> specifiedReadings) 
            : label(specifiedLabel), 
            readings(specifiedReadings){};
    Measure(){};
} Measure;

/**
 * @brief SimulatorInfo structure that holds the information about a simulator.
 * 
 * @param simulatorName - the name of the simulator
 * @param simulatorVersion - the version of the simulator
 * @param nativeOutputType - the native output type of the simulator    
 * @param functions - the functions that the simulator supports
 * @param parameters - the parameters that the simulator supports
 * @param metrics - the metrics that the simulator supports
 * @param buildOptions - the build options that the simulator supports
 * @details This structure is used to hold the information about the simulator that is read from the simulation configuration file.
 * The entirety of this structure isn't optional, this is since the framework needs to know what simulator it is working with, what version it is and what it supports.
 * Therefore a new simulator must be defined with a simulation configuration file.
 */
typedef struct SimulatorInfo {
    std::string simulatorName;
    std::string simulatorVersion;
    std::string nativeOutputType;
    std::vector<std::string> functions;
    std::vector<std::string> supportedParameters; //maybe change to a vector of Parameter
    std::vector<std::string> supportedMetrics; //maybe change to a vector of Metrics
    std::vector<std::string> supportedBuildOptions; //maybe change to a vector of BuildOptions

    SimulatorInfo(const std::string& simulatorName  = "", 
                const std::string& simulatorVersion = "", 
                const std::string& nativeOutputType = "", 
                const std::vector<std::string>& functions   = {}, 
                const std::vector<std::string>& parameters  = {},
                const std::vector<std::string>& metrics     = {},
                const std::vector<std::string>& buildOptions = {}) 
                : simulatorName(simulatorName), 
                simulatorVersion(simulatorVersion), 
                nativeOutputType(nativeOutputType), 
                functions(functions), 
                supportedParameters(parameters),
                supportedMetrics(metrics),
                supportedBuildOptions(buildOptions){}
} SimulatorInfo;

#endif



