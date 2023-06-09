#include <iostream>
#include <core.Scenario.hpp>
#include <unordered_map>

class ScenarioManager {
public:
    ScenarioManager() {}

    std::unordered_map<std::string, std::unique_ptr<Scenario>> scenarios;
    std::string active_scenario;

    bool CheckActiveScenario() {
        if(active_scenario.empty()){
            std::cout << "No active scenario, please select a scenario first\n";
            return false;
        }
        return true;
    }

    void ListScenarios() {
        if(scenarios.empty()){
            std::cout << "No scenarios created yet\n";
        } else {
            std::cout << "List of available scenarios:\n";
            for(const auto& scenario : scenarios){
                std::cout << "- " << scenario.first << "\n";
            }
        }
    }

    void CreateScenario(const std::string& scenario_name) {
        if(scenarios.find(scenario_name) != scenarios.end()){
            std::cout << "A scenario with the name " << scenario_name << " already exists.\n";
            return;
        }
        scenarios[scenario_name] = std::make_unique<Scenario>();
        std::cout << "Scenario " << scenario_name << " created successfully!\n";
    }

    void RemoveScenario(const std::string& scenario_name) {
        if(scenarios.find(scenario_name) == scenarios.end()){
            std::cout << "Scenario with the name " << scenario_name << " does not exist.\n";
            return;
        }
        scenarios.erase(scenario_name);
        std::cout << "Scenario " << scenario_name << " removed successfully!\n";
    }

    void SelectScenario(const std::string& scenario_name) {
        if(scenarios.find(scenario_name) == scenarios.end()){
            std::cout << "Scenario with the name " << scenario_name << " does not exist.\n";
            return;
        }
        active_scenario = scenario_name;
        std::cout << "Selected scenario: " << scenario_name << "\n";
    }
};

