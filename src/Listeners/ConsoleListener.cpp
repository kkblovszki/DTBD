#include "../Include/Listener.hpp"

using namespace Core::Listeners;

ConsoleListener::ConsoleListener(){
    std::cout << "ConsoleListener created" << std::endl;
}

ConsoleListener::~ConsoleListener(){
    std::cout << "ConsoleListener destroyed" << std::endl;
}

void ConsoleListener::OnSimulationStart() {
    std::cout << "ConsoleListener started" << std::endl;
}

void ConsoleListener::OnSimulationEnd() {
    std::cout << "ConsoleListener ended" << std::endl;
}

void ConsoleListener::OnSimulationUpdate(std::string value){
    std::cout << value << std::endl;
}

void ConsoleListener::OnSimulationResult(){
    std::cout << "ConsoleListener result" << std::endl;
}