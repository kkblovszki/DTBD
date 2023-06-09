#include <iostream>
#include <core.Benchmark.hpp>
#include <unordered_map>

class BenchmarkManager {
public:
    BenchmarkManager() {}

    std::unordered_map<std::string, std::unique_ptr<Benchmark>> benchmarks;
    std::string active_benchmark;

    bool CheckActiveBenchmark() {
        if(active_benchmark.empty()){
            std::cout << "No active benchmark, please select a benchmark first\n";
            return false;
        }
        return true;
    }

    void ListBenchmarks() {
        if(benchmarks.empty()){
            std::cout << "No benchmarks created yet\n";
        } else {
            std::cout << "List of available benchmarks:\n";
            for(const auto& benchmark : benchmarks){
                std::cout << "- " << benchmark.first << "\n";
            }
        }
    }

    void CreateBenchmark(const std::string& benchmark_name) {
        if(benchmarks.find(benchmark_name) != benchmarks.end()){
            std::cout << "A benchmark with the name " << benchmark_name << " already exists.\n";
            return;
        }
        benchmarks[benchmark_name] = std::make_unique<Benchmark>();
        std::cout << "Benchmark " << benchmark_name << " created successfully!\n";
    }

    void RemoveBenchmark(const std::string& benchmark_name) {
        if(benchmarks.find(benchmark_name) == benchmarks.end()){
            std::cout << "Benchmark with the name " << benchmark_name << " does not exist.\n";
            return;
        }
        benchmarks.erase(benchmark_name);
        std::cout << "Benchmark " << benchmark_name << " removed successfully!\n";
    }

    void SelectBenchmark(const std::string& benchmark_name) {
        if(benchmarks.find(benchmark_name) == benchmarks.end()){
            std::cout << "Benchmark with the name " << benchmark_name << " does not exist.\n";
            return;
        }
        active_benchmark = benchmark_name;
        std::cout << "Selected benchmark: " << benchmark_name << "\n";
    }
};