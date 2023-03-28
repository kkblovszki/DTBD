#ifndef TESTBED_HPP
#define TESTBED_HPP

#include "core.Benchmark.hpp"

class Testbed
{
private:
    /* data */
public:
    Testbed();
    ~Testbed();

    std::map<std::string, std::unique_ptr<Benchmark>> benchmarks;

    void CreateBenchmark(std::string benchmarkName);
    void RemoveBenchmark(std::string benchmarkName);
    void LoadBenchmarkConfig(std::string benchmarkName, std::string configPath);
    
};

#endif