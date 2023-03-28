#include "../Include/Listener.hpp"

using namespace Core::Listeners;

TestListener::TestListener(){
    std::cout << "Test listener created" << std::endl;
}

TestListener::~TestListener(){
    std::cout << "Test listener destroyed" << std::endl;
}

void TestListener::OnSimulationStart(std::vector<Metrics> metrics) {
    std::cout << "Simulation started" << std::endl;
}

void TestListener::OnSimulationEnd(){
    std::cout << "Simulation ended" << std::endl;
}

void TestListener::OnSimulationUpdate(std::string value) {
    std::cout << "Simulation updated" << std::endl;
}

void TestListener::OnSimulationResult() {
    std::cout << "Simulation result" << std::endl;
}
