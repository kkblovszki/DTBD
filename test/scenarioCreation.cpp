#include "./src/include/core.Scenario.hpp"
#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<Scenario> singleScenario = std::make_unique<Scenario>("Scenario_1", "scenario instantiation unit test", "TestListener");

    return 0;
}
