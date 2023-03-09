#ifndef SIMULATOR_CREATOR_HPP
#define SIMULATOR_CREATOR_HPP
#include "core.Types.hpp"
#include "SimulatorMockUpInterface.hpp"

//! \class SimulatorCreator
//! \brief This class is responsible for creating the simulator instances
//! \details This class is responsible for creating the simulator instances. It contains a map of strings to simulator types, which is used to create the simulator instances. 
//! \author Mikkel Silkeborg & Asbjørn Nielsen 
//! \date 2020-08-28
//! \version 0.1
//! \bug none
//! \todo none
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