#include <iostream>
#include <cassert>
#include <core.Testbed.hpp>

#define DEBUG

int main(int argc, char** argv) {
    Testbed testbed;
    
    testbed.CreateBenchmark("testBenchmark");

    assert(testbed.benchmarks["testBenchmark"] == nullptr);
    std::cout << "Benchmark created" << std::endl;

    return 0;
}