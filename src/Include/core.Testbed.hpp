#include "core.benchmark.hpp"

class Testbed
{
private:
    /* data */
public:
    Testbed(/* args */);
    ~Testbed();

    std::map<std::string, Benchmark> benchmarks;

    void CreateBenchmark(std::string benchmarkName){
        //benchmarks[benchmarkName] = Benchmark();
    };

    void RemoveBenchmark(std::string benchmarkName){
        //benchmarks[benchmarkName].~Benchmark();
        //benchmarks.erase(benchmarkName);
    };

    void LoadBenchmarkConfig(std::string benchmarkName, std::string configPath){
        benchmarks[benchmarkName].LoadSimulationConfig(configPath);
    };


};