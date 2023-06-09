
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

#include "../include/core.Benchmark.hpp"
#include "../include/core.Scenario.hpp"
#include "../include/core.Testbed.hpp"


/**
 * @brief A Command Line Interface (CLI) for managing and interacting with testbeds and benchmarks.
 * 
 * \page DTDB_CLI DTDB_CLI
 *  
 * The DTDB_CLI class provides a command line interface for users to interact with 
 * a system of testbeds, benchmarks, and scenarios. It provides an easy-to-use interface 
 * for creating, managing, and executing these components. 
 *
 * The class stores active testbed and benchmark information and has the capability 
 * to process and execute various commands input by the user. The following key functionalities 
 * are provided:
 *
 *  - Testbed management: Users can create, select, list, and remove testbeds.
 *  - Benchmark management: Within a selected testbed, users can create, select, list, 
 *    and remove benchmarks, as well as load benchmark configurations.
 *  - Scenario management: Within a selected benchmark, users can create, list, remove scenarios, 
 *    and run scenarios with or without parameters.
 *  
 * The DTDB_CLI class utilizes a command processor to interpret and execute commands input 
 * by the user. These commands are tokenized and processed individually to perform the requested 
 * operation on the relevant component (Testbed, Benchmark, or Scenario).
 *
 * \note The class does not directly manage the underlying details of the Testbed, Benchmark, 
 *       or Scenario objects, but instead delegates these tasks to the appropriate classes.
 */
class DTDB_CLI {
   
    public:
         DTDB_CLI(){}
        ~DTDB_CLI(){}
        void RunCLI(); //Run the CLI    

    private:
        std::string active_testbed = "";  //The active testbed
        std::unordered_map<std::string, std::unique_ptr<Testbed>> testbeds;  //A map of created testbeds. The key is the testbed name.

        std::string active_benchmark = "";  //The active benchmark

        std::vector<std::string> tokens;  //A vector of tokens from the user input

    private:

        bool CheckActiveTestbedAndBenchmark(){
            if (active_testbed.empty()) {
                std::cout << "No active testbed, please select a testbed first\n";
                return false;
            }else if(active_benchmark.empty()){
                std::cout << "No active benchmark, please select a benchmark first\n";
                return false;
            }

            return true;
        }

        void ListTestbed() {
            if (testbeds.empty()) {
                std::cout << "No testbeds created yet\n";
            } else {
                std::cout << "List of available testbeds:\n";
                for (const auto &testbed : testbeds) {
                    std::cout << "- " << testbed.first << "\n";
                }
            }
        }

        std::vector<std::string> Tokenize(const std::string &input) {
            std::istringstream iss(input);
            std::vector<std::string> tokens;
            std::string token;
            while (iss >> token) {
              tokens.push_back(token);
            }
            return tokens;
        }

        void CreateTestbed(const std::string& testbed_name) {
            // Check if testbed with the given name already exists
            if (testbeds.find(testbed_name) != testbeds.end()) {
              std::cout << "A testbed with the name " << testbed_name << " already exists.\n";
              return;
            }

            // Create the testbed
            testbeds[testbed_name] = std::make_unique<Testbed>(); 
            std::cout << "Testbed " << testbed_name << " created successfully!\n";
        }

        void RemoveTestbed(const std::string& testbed_name) {
            // Check if testbed with the given name exists
            if (testbeds.find(testbed_name) == testbeds.end()) {
                std::cout << "Testbed with the name " << testbed_name << " does not exist.\n";
                return;
            }

            // Remove the testbed
            testbeds.erase(testbed_name);
            std::cout << "Testbed " << testbed_name << " removed successfully!\n";
        }

        void SelectTestbed(const std::string& testbed_name) {
          // Check if testbed with the given name exists
          if (testbeds.find(testbed_name) == testbeds.end()) {
            std::cout << "Testbed with the name " << testbed_name << " does not exist.\n";
            return;
          }

          active_testbed = testbed_name;
          std::cout << "Selected testbed: " << testbed_name << "\n";
        }

        void SelectBenchmark(const std::string& benchmark_name) {
            // Check if benchmark with the given name exists
            if (testbeds[active_testbed]->benchmarks.find(benchmark_name) == testbeds[active_testbed]->benchmarks.end()) {
                std::cout << "Benchmark with the name " << benchmark_name << " does not exist in " << active_testbed << ".\n";
                return;
            }

            active_benchmark = benchmark_name;
            std::cout << "Selected benchmark: " << benchmark_name << "\n";
        }

        void ProcessToken(std::vector<std::string> tokens)  {
            
            std::string cmd = tokens[0];
            if (cmd == "help") {
                std::cout << "Available commands:\n"
                          << "\tcreate_testbed <testbed_name> - creates a new testbed\n"
                          << "\tremove_testbed <testbed_name> - removes an existing testbed\n"
                          << "\tselect_testbed <testbed_name> - selects an existing testbed as workspace\n"
                          << "\tlist_testbeds - Lists all created testbeds \n"
                          << "\tcreate_benchmark <benchmark_name> - creates a benchmark\n"
                          << "\tselect_benchmark <benchmark_name> - selects an existing benchmark\n"
                          << "\tremove_benchmark <benchmark_name> - removes a benchmark\n"
                          << "\tlist_benchmarks\n"
                          << "\tload_benchmark_config <benchmark_name> <config_path>\n"
                          << "\tcreate_scenario <scenario_name>\n"
                          << "\tremove_scenario <scenario_name>\n"
                          << "\tlist_scenarios <benchmark_name>\n"
                          << "\tcreate_all_scenarios\n"
                          << "\trun_scenario <scenario_name>\n"
                          << "\trun_scenario_with_params <scenario_name>\n"
                          << "\trun_scenarios_using_strategy\n"
                          << "\thelp\n"
                          << "\texit\n\n";
            }
            else if (cmd == "create_testbed") {
                if (tokens.size() < 2) {
                    std::cout << "Usage: create_testbed <testbed_name>\n";
                }
                else {
                    CreateTestbed(tokens[1]);
                }
            }
            else if (cmd == "select_testbed") {
                if (tokens.size() < 2) {
                    std::cout <<"Usage: select_testbed <testbed_name>\n";
                }
                else {
                    SelectTestbed(tokens[1]);
                }
            }
            else if (cmd == "remove_testbed") {
                if (tokens.size() < 2) {
                    std::cout <<"Usage: remove_testbed <testbed_name>\n";
                }
                else {
                    RemoveTestbed(tokens[1]);
                }
            }
            else if (cmd == "list_testbeds") {
                ListTestbed();
            }
            else if (cmd == "create_benchmark") {
                if (tokens.size() < 2) {
                    std::cout <<"Usage: create_benchmark <benchmark_name>\n";
                }
                else {
                    testbeds[active_testbed]->CreateBenchmark(tokens[1]);
                }
            }
            else if(cmd == "select_benchmark"){
                if(active_testbed.empty()){
                    std::cout <<"Please select a testbed first.\n";
                }
                if (tokens.size() < 2) {
                    std::cout <<"Usage: select_benchmark <benchmark_name>\n";
                }
                else {
                    SelectBenchmark(tokens[1]);
                }
            }
            else if (cmd == "load_benchmark_config") {
              if (tokens.size() < 2) {
                std::cout <<"Usage: load_benchmark <benchmark_config_file_path>\n";
              } else {
                std::string benchmark_config_file_path = tokens[1];
                try {
                    testbeds[active_testbed]->LoadBenchmarkConfig(active_benchmark, benchmark_config_file_path);
                } catch (const std::exception& ex) {
                    std::cout <<"Failed to load benchmark: " << ex.what() << "\n";
                }
              }
            }
            else if (cmd == "list_benchmarks") {
                if (active_testbed.empty()) {
                    std::cout <<"No active testbed, please select a testbed first\n";
                } else {
                    auto & testbed = testbeds[active_testbed];
                    auto & benchmark_names = testbed->benchmarks;
                    std::cout << "Benchmarks in testbed '" + active_testbed + "':\n";
                    for (const auto & [benchmark_name, _]: benchmark_names) {
                      std::cout << " - " << benchmark_name << "\n";
                    }
                }
            }
            else if (cmd == "list_scenarios") {
              if (active_testbed.empty()) {
                std::cout << "No active testbed, please select a testbed first\n";
              } else {
                auto& testbed = testbeds[active_testbed];
                auto& scenario_names = testbed->benchmarks[active_benchmark]->scenarios;

                std::cout << "Scenarios in testbed '" << active_testbed << "':\n";
                for (const auto & [name, _] : scenario_names) {
                  std::cout << "- " << name << "\n";
                }
              }
            } else if (cmd == "create_scenario") {
              if (active_testbed.empty()) {
                std::cout << "No active testbed, please select a testbed first\n";
              } else if (tokens.size() < 2) {
                std::cout << "Usage: add_scenario <scenario_name>\n";
              } else {
                auto & testbed = testbeds[active_testbed];
                auto & benchmark = testbed->benchmarks[active_benchmark];
                std::string scenario_name = tokens[1];
                try {
                  benchmark->CreateScenario(tokens[1]);
                  std::cout << "Scenario '" << scenario_name << "' added to benchmark: '" << active_benchmark << "'\n";
                } catch (const std::exception & ex) {
                  std::cerr << "Failed to add scenario: " << ex.what() << "\n";
                }
              }
            } else if (cmd == "remove_scenario") {
              if (active_testbed.empty()) {
                std::cout << "No active testbed, please select a testbed first\n";
              } else if (tokens.size() < 2) {
                std::cout << "Usage: remove_scenario <scenario_name>\n";
              } else {
                auto & testbed = testbeds[active_testbed];
                std::string scenario_name = tokens[1];
                try {
                  testbed->benchmarks[active_benchmark]->RemoveScenario(scenario_name);
                  std::cout << "Scenario '" << scenario_name << "' removed from benchmark '" << active_benchmark << "'\n";
                } catch (const std::exception & ex) {
                  std::cerr << "Failed to remove scenario: " << ex.what() << "\n";
                }
              }
            } else if (cmd == "remove_scenario") {
              if (active_testbed.empty()) {
                std::cout << "No active testbed, please select a testbed first\n";
              } else if (tokens.size() < 2) {
                std::cout << "Usage: remove_scenario <scenario_name>\n";
              } else {
                auto &testbed = testbeds[active_testbed];
                auto &benchmark = testbed->benchmarks[active_benchmark];
                std::string scenario_name = tokens[1];
                try {
                  benchmark->RemoveScenario(scenario_name);
                  std::cout << "Scenario '" << scenario_name << "' removed from benchmark '" << active_benchmark << "'\n";
                } catch (const std::exception &ex) {
                  std::cerr << "Failed to remove scenario: " << ex.what() << "\n";
                }
              }
            } else if (cmd == "create_all_scenarios") {
              if (active_testbed.empty()) {
                std::cout << "No active testbed, please select a testbed first\n";
              } else {
                auto &testbed = testbeds[active_testbed];
                auto &benchmark = testbed->benchmarks[active_benchmark];
                try {
                  benchmark->CreateAllScenarios();
                  std::cout << "All scenarios created for Benchmark: '" << active_benchmark << "'\n";
                } catch (const std::exception &ex) {
                  std::cerr << "Failed to create all scenarios: " << ex.what() << "\n";
                }
              }
            } else if (cmd == "run_scenario") {
              if (!CheckActiveTestbedAndBenchmark()) {
                std::cout << "No active testbed or benchmark, please select a testbed and benchmark first\n";
              } else if (tokens.size() < 2) {
                std::cout << "Usage: run_scenario <scenario_name>\n";
              } else {
                auto& testbed = testbeds[active_testbed];
                auto& benchmark = testbed->benchmarks[active_benchmark];
                std::string scenario_name = tokens[1];
                try {
                  benchmark->RunScenario(scenario_name);
                } catch (const std::exception &ex) {
                  std::cerr << "Failed to run scenario: " << ex.what() << "\n";
                }
              }
            } else if (cmd == "run_scenario_with_params") {
              if (!CheckActiveTestbedAndBenchmark()) {
                std::cout << "No active testbed or benchmark, please select a testbed and benchmark first\n";
              } else if (tokens.size() < 2) {
                std::cout << "Usage: run_scenario_with_params <scenario_name>\n";
              } else {
                auto& testbed = testbeds[active_testbed];
                auto& benchmark = testbed->benchmarks[active_benchmark];
                std::string scenario_name = tokens[1];
                std::vector<std::string> scenario_params(tokens.begin() + 2, tokens.end());
                try {
                  benchmark->RunScenarioWithParameters(scenario_name);
                } catch (const std::exception &ex) {
                  std::cerr << "Failed to run scenario with params: " << ex.what() << "\n";
                }
              }
            } else if (cmd == "run_scenarios_using_strategy") {
              if (active_testbed.empty()) {
                std::cout << "No active testbed, please select a testbed first\n";
              } else {
                auto& testbed = testbeds[active_testbed];
                auto& benchmark = testbed->benchmarks[active_benchmark];
                try {
                  benchmark->RunScenariosUsingStrategy();
                } catch (const std::exception &ex) {
                  std::cerr << "Failed to run scenarios using strategy: " << ex.what() << "\n";
                }
              }
            } else if (cmd == "remove_benchmark") {
                if (active_testbed.empty()) {
                    std::cout << "No active testbed, please select a testbed first\n";
                } else {
                    std::string benchmark_name;
                    std::cout << "Enter the name of the benchmark to remove: ";
                    std::cin >> benchmark_name;

                    auto &testbed = testbeds[active_testbed];
                    try {
                        testbed->RemoveBenchmark(benchmark_name);
                    } catch (const std::exception &ex) {
                        std::cerr << "Failed to remove benchmark: " << ex.what() << "\n";
                    }
                }
            } else if (cmd == "exit") {
                std::cout << "Exiting...\n";
                exit(0);
            } else {
                std::cout << "Invalid command\n";
            }
            
            return;
        }
    
};

void DTDB_CLI::RunCLI() {
    std::string command;

    while (true) {
        // Print active testbed and benchmark
        // Check if active testbed and benchmark are undefined
        if (CheckActiveTestbedAndBenchmark()) {
            std::cout << "Active testbed: " << active_testbed << "\n";
            std::cout << "Active benchmark: " << active_benchmark << "\n";
        }

        std::cout << "==============================\n"
                  << "Welcome to the DTDB CLI!\n"
                  << "==============================\n"
                  << "Available commands:\n"
                  << "\t---- Testbed commands ----\n"
                  << "\tcreate_testbed <testbed_name>\n"
                  << "\tselect_testbed <testbed_name>\n"
                  << "\tremove_testbed <testbed_name>\n"
                  << "\tlist_testbeds\n"
                  << "\t---- Benchmark commands ----\n"
                  << "\tcreate_benchmark <benchmark_name>\n"
                  << "\tselect_benchmark <benchmark_name>\n"
                  << "\tremove_benchmark <benchmark_name>\n"
                  << "\tlist_benchmarks\n"
                  << "\tload_benchmark_config <config_path>\n"
                  << "\t---- Scenario commands ----\n"
                  << "\tcreate_scenario <scenario_name>\n"
                  << "\tremove_scenario <scenario_name>\n"
                  << "\tlist_scenarios\n"
                  << "\tcreate_all_scenarios\n"
                  << "\trun_scenario <scenario_name>\n"
                  << "\trun_scenario_with_params <scenario_name>\n"
                  << "\trun_scenarios_using_strategy\n"
                  << "\thelp\n"
                  << "\texit\n\n";
        std::cout << "Enter a command: ";
        std::getline(std::cin, command);
        std::cout << "\n";

        tokens = Tokenize(command);
        
        if (tokens.empty()) {
            continue;
        }

        ProcessToken(tokens);
    }
    return;
};