#ifndef TESTBED_HPP

#include "core.Benchmark.hpp"

class Testbed
{
private:
    /* data */
public:
    Testbed();
    ~Testbed();

    std::map<std::string, Benchmark> benchmarks;

    void CreateBenchmark(std::string benchmarkName);
    void RemoveBenchmark(std::string benchmarkName);
    void LoadBenchmarkConfig(std::string benchmarkName, std::string configPath);
    
};

#endif