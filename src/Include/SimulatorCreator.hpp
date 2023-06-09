#ifndef SIMULATOR_CREATOR_HPP
#define SIMULATOR_CREATOR_HPP

#include "core.Types.hpp"
#include "SimulatorMockUpInterface.hpp"
#include <bit>


/**
 * @brief SimulatorCreator class
 * 
 * \page SimulatorCreator SimulatorCreator
 * 
 * The SimulatorCreator class is responsible for creating the simulator instances. It contains a map of strings to simulator types, which is used to create the simulator instances.
 * 
 * The SimulatorCreator class have the following functions:
 * 
 * @li SimulatorCreator::stringForceUpperCase(std::string inputString)
 * @li SimulatorCreator::stringToSimType()
 * @li SimulatorCreator::CreateSimulator(const std::string& simulatorName)
 * 
 * @see SimulatorCreator.cpp for implementation
 * 
 */
class SimulatorCreator{
    
protected:
    enum class SimulatorType {
        EVOCRAFT,
        ALCHEMIST,
        NS3
    };
    
private:
    static const std::string stringForceUpperCase(std::string inputString){
        std::transform(inputString.begin(), inputString.end(), inputString.begin(), ::toupper);
        return inputString;
    }

    static const std::map<std::string, SimulatorType>& stringToSimType();
    
public:
    static std::unique_ptr<SimulatorMockUpInterface> CreateSimulator(const std::string& simulatorName);
};

#endif