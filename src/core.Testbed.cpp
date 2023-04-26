#include "Include/core.Testbed.hpp"


Testbed::Testbed(){}
Testbed::~Testbed(){}

/**
 * @brief 
 * 
 */
std::vector<std::string> Testbed::ListBenchmarks(bool verbose){

    std::vector<std::string> benchmarkNameList = {};
    
    for(auto& benchmark : benchmarks){
        if(verbose == true){
            std::cout << benchmark.first << std::endl;    
        }

        benchmarkNameList.emplace_back(benchmark.first);
    }       

    return benchmarkNameList;
}

/**
 * @brief Add new Benchmark to the Testbed.
 * @param benchmarkName 
 */
void Testbed::CreateBenchmark(std::string benchmarkName){
    benchmarks[benchmarkName] = std::make_unique<Benchmark>();
};

/**
 * @brief Remove specified benchmark from the Testbed.
 * @param benchmarkName 
 */
void Testbed::RemoveBenchmark(std::string benchmarkName){
    benchmarks[benchmarkName].reset();
    benchmarks.erase(benchmarkName);
};

/**
 * @brief 
 * 
 * @param benchmarkName 
 * @param configPath 
 */
void Testbed::LoadBenchmarkConfig(std::string benchmarkName, std::string configPath){
    if(benchmarks.find(benchmarkName) == benchmarks.end() || benchmarks.empty()) {
        std::cerr << "Benchmark " << benchmarkName << " not found." << std::endl;
        return;
    }else{
        benchmarks[benchmarkName]->LoadSimulationConfig(configPath);
    }
};