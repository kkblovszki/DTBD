#include "../Include/Listener.hpp"

using namespace Core::Listeners;

DefaultListener::DefaultListener(){
    std::cout << "DefaultListener created" << std::endl;
};

DefaultListener::~DefaultListener(){
    std::cout << "DefaultListener destroyed" << std::endl;
};

void DefaultListener::OnSimulationStart() {
    std::cout << "Simulation started" << std::endl;
}

void DefaultListener::OnSimulationEnd() {
    std::cout << "Simulation ended" << std::endl;
}

void DefaultListener::OnSimulationUpdate(std::string value){
    std::cout << "Simulation updated" << std::endl;
}

void DefaultListener::OnSimulationResult(){
    std::cout << "Simulation result" << std::endl;
}