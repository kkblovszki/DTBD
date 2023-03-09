#include "NS3Interface.hpp"


NS3Interface::NS3Interface() {
    simulator = SimulatorInfo();
    APIFunctionPassThrough = {};
}

void NS3Interface::setLibraryHandle(void* libraryHandle) {
    auto libHandle = static_cast<void*>(libraryHandle);
    ns3LibHandler = libHandle;
};

void NS3Interface::LoadConfiguration(std::string configFileName) {
    
};

void NS3Interface::WriteToConfiguration(std::string configFileName) {

};

void NS3Interface::LoadProblem(std::map<std::string, std::string> CoreProblemCallback()) {

};

void NS3Interface::LoadMetrics() {

};

void NS3Interface::RunSimulation(){

};

void NS3Interface::GetRuntimeData(){

};

