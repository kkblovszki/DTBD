#include <iostream>
#include <cassert>
#include <core.Testbed.hpp>

#define DEBUG 1

int main(int argc, char** argv) {
    Testbed testbed;
    
    testbed.CreateBenchmark("testBenchmark");

    assert(testbed.benchmarks["testBenchmark"] != nullptr);

    testbed.benchmarks["testBenchmark"]->CreateScenario("testScenario");

    assert(testbed.benchmarks["testBenchmark"]->scenarios["testScenario"] != nullptr);

    std::cout << "Benchmark created" << std::endl;

    return 0;
}