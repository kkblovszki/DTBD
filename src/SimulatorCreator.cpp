#include "include/SimulatorCreator.hpp"
#include <dlfcn.h>

SimulatorCreator::SimulatorCreator(/* args */){}
SimulatorCreator::~SimulatorCreator(){}

void SimulatorCreator::CreatePublisher(SimulatorType type){};
void SimulatorCreator::CreateSubscriber(SimulatorType type){};

const std::map<std::string, SimulatorCreator::SimulatorType>& SimulatorCreator::stringToSimType() {
    static const std::map<std::string, SimulatorType> simMap = {
        {"EVOCRAFT", SimulatorType::EVOCRAFT},
        {"ALCHEMIST", SimulatorType::ALCHEMIST},
        {"NS3", SimulatorType::NS3}
    };
        
    return simMap;
}

std::unique_ptr<SimulatorMockUpInterface> SimulatorCreator::CreateSimulator(const std::string& simulatorName){
    auto stringType = stringToSimType().find(simulatorName);
    if (stringType == stringToSimType().end()) {
        throw std::invalid_argument("Unsupported Simulator");
    }
    
    SimulatorType type = stringType->second;

    switch (type) {
    case SimulatorType::EVOCRAFT:
        dlopen();
        return std::make_unique<EvocraftSimulator>();
        
    case SimulatorType::ALCHEMIST:
        dlopen();
        return std::make_unique<AlchemistSimulator>();
        
    case SimulatorType::NS3:
        dlopen();
        return std::make_unique<NS3Interface>();
    }
    return nullptr;
};

