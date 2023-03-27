#include "Include/core.Testbed.hpp"

Testbed::Testbed(){ }

Testbed::~Testbed(){ }


std::map<std::string, Benchmark> benchmarks;

void Testbed::CreateBenchmark(std::string benchmarkName){
   //benchmarks[benchmarkName] = std::move(Benchmark());
};

void Testbed::RemoveBenchmark(std::string benchmarkName){
    //benchmarks.erase(benchmarkName);
};

void Testbed::LoadBenchmarkConfig(std::string benchmarkName, std::string configPath){
    benchmarks[benchmarkName].LoadSimulationConfig(configPath);
};