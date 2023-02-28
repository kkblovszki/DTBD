#ifndef CORE_TYPES_HPP
#define CORE_TYPES_HPP
#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <memory>
#include <functional>

typedef struct Metrics {
    std::string name;
    std::string unit;

    Metrics(){name = 'NULL'; unit = 'NULL';};
    Metrics(std::string specifiedName, std::string specifiedUnit){name = specifiedName; unit = specifiedUnit;}
    ~Metrics(){};
} Metrics;

typedef struct Measure {
    Metrics metric;
    std::string label;
    std::vector<std::string> readings;

    Measure(){metric = Metrics(); label = 'NULL'; readings = {};};
    ~Measure(){};
    Measure(Metrics specifiedMetric, std::string specifiedLabel, std::vector<std::string> specifiedReadings) {
        metric = specifiedMetric; 
        label = specifiedLabel;
        readings = specifiedReadings;
    };
} Measure;

typedef struct SimulatorInfo {
    std::string simulatorName;
    std::string simulatorVersion;
    std::string nativeOutputType;
    std::vector<std::string> functions;
    std::vector<std::string> parameters;

    SimulatorInfo() {
        simulatorName = 'NULL';
        simulatorVersion = 'NULL';
        nativeOutputType = 'NULL';
        functions = {};
        parameters = {};
    };
    ~SimulatorInfo(){};
    SimulatorInfo(std::string specifiedName, 
                  std::string specifiedVersion,
                  std::string specifiedOutputType,
                  std::vector<std::string> specifiedFunctions, 
                  std::vector<std::string> specifiedParamaters) {
        simulatorName = specifiedName;
        simulatorVersion = specifiedVersion;
        nativeOutputType = specifiedOutputType;
        functions = specifiedFunctions;
        parameters = specifiedParamaters;
    };

} SimulatorInfo;

#endif



