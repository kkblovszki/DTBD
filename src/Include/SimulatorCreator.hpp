#ifndef SIMULATOR_CREATOR_HPP
#define SIMULATOR_CREATOR_HPP
#include "core.Types.hpp"
#include "SimulatorMockUpInterface.hpp"


class SimulatorCreator
{
protected:
    enum class SimulatorType {
        EVOCRAFT,
        ALCHEMIST,
        NS3
    };
    
private:
    static const std::map<std::string, SimulatorType>& stringToSimType();
    
public:
    //SimulatorCreator();
    ~SimulatorCreator();
    
    void CreatePublisher(SimulatorType type);
    void CreateSubscriber(SimulatorType type);
    
    static std::unique_ptr<SimulatorMockUpInterface> CreateSimulator(const std::string& simulatorName);
};









#endif