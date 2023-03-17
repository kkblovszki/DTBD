#include "Include/core.Testbed.hpp"

Testbed::Testbed()
{ 
}

Testbed::~Testbed()
{
}


std::map<std::string, Benchmark> benchmarks;

void Testbed::CreateBenchmark(std::string benchmarkName){
    //benchmarks[benchmarkName] = Benchmark();
    throw std::runtime_error("Not implemented yet");
};

void Testbed::RemoveBenchmark(std::string benchmarkName){
    //benchmarks[benchmarkName].~Benchmark();
    //benchmarks.erase(benchmarkName);
    throw std::runtime_error("Not implemented yet");
};

void Testbed::LoadBenchmarkConfig(std::string benchmarkName, std::string configPath){
    benchmarks[benchmarkName].LoadSimulationConfig(configPath);
};