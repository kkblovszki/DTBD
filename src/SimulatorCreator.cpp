#include "include/SimulatorMockUpInterface.hpp"

class SimulatorCreator
{
private:
    enum class SimulatorType{
        Evocraft,
        Alchemist,
        NS3
    };
public:
    SimulatorCreator(/* args */);
    ~SimulatorCreator();
    
    void CreatePublisher(SimulatorType type){};
    void CreateSubscriber(SimulatorType type){};
    
    static std::unique_ptr<SimulatorCreator> CreateSimulator(SimulatorType type){
        switch (type) {
        case SimulatorType::Evocraft:
            return std::make_unique<EvocraftSimulator>();
        
        case SimulatorType::Alchemist:
            return std::make_unique<AlchemistSimulator>();
        
        case SimulatorType::NS3:
            return std::make_unique<NS3Simulator>();
        
        default:
            return nullptr;
        }
    };
};

SimulatorCreator::SimulatorCreator(/* args */){}
SimulatorCreator::~SimulatorCreator(){}
