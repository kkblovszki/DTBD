#ifndef TESTBED_HPP
#define TESTBED_HPP

#include "core.Benchmark.hpp"

class Testbed
{
private:
    
public:
    Testbed();
    ~Testbed();
    
    std::map<std::string, std::unique_ptr<Benchmark>> benchmarks;

    void CreateBenchmark(std::string benchmarkName);
    void RemoveBenchmark(std::string benchmarkName);
    std::vector<std::string> ListBenchmarks(bool verbose = false);
    void LoadBenchmarkConfig(std::string benchmarkName, std::string configPath);
    
};

#endif