#ifndef SIMULATOR_MOCKUP_INTERFACE_HPP
#define SIMULATOR_MOCKUP_INTERFACE_HPP

#include "core.Types.hpp"
#include "AbstractListener.hpp"
#include <functional>

/**
 * @brief This class is an mockup interface for a simulator.
 * @class SimulatorMockUpInterface
 * @version 1.0
 * @details The SimulatorMockUpInterface is an interface for the simulator. It contains all the functions that a simulator should implement.
 * The class is an abstract class, which means that it cannot be instantiated. It is used to create a common interface for the simulators.
 * The class contains a map of strings to functions, which can be used to implement a DSL language. 
 * 
 * @class SimulatorMockUpInterface contains the following functions:
 *
 * @fn SimulatorMockUpInterface::SimulatorMockUpInterface()
 * @fn SimulatorMockUpInterface::~SimulatorMockUpInterface()
 * @fn SimulatorMockUpInterface::GetSimulatorInfo()
 * @fn SimulatorMockUpInterface::SetLibraryHandle(void* libraryHandle)
 * @fn SimulatorMockUpInterface::SetListener(std::unique_ptr<Listener> newListener)
 * @fn SimulatorMockUpInterface::LoadConfiguration(std::string simulatorVersion)
 * @fn SimulatorMockUpInterface::AddBuildOptions(std::vector<BuildOptions> buildOptions)
 * @fn SimulatorMockupInterface::WriteToConfiguration(std::string configFileName)
 * @fn SimulatorMockUpInterface::LoadParameters(std::vector<Parameter> parameter)
 * @fn SimulatorMockUpInterface::LoadMetrics(std::vector<Metrics> metrics)
 * @fn SimulatorMockUpInterface::RunSimulation()
 * 
 * For instantiation of SMI's based on @class SimulatorMockupInterface @see SimulatorCreator.hpp
 */
class SimulatorMockUpInterface
{
protected:
     SimulatorInfo simulatorInfo; //Contains all the simulator information.

private:
    std::map<std::string, std::function<std::unique_ptr<void()>()>> APIFunctionPassThrough; //Contains API functions a simulator contains, can be used to implement a DSL language.
    std::unique_ptr<Listener> activeSimulatorListener; //Contains the active listener for the simulator.

public:
    SimulatorMockUpInterface(){};
    ~SimulatorMockUpInterface(){};
    //SimulatorMockUpInterface(SimulatorInfo specifiedSimulator, std::map<std::string,int> specifiedAPIFunction);
    
    /**
     * @brief Get the Simulator Info object
     * 
     * @return SimulatorInfo 
     */
    virtual SimulatorInfo GetSimulatorInfo() = 0;

    /**
     * @brief Set the Library Handle object
     * 
     * @param libraryHandle 
     */
    virtual void setLibraryHandle(std::shared_ptr<void> libraryHandle) = 0;

    /**
     * @brief Set the Listener object
     * 
     * @param uniqueListener 
     */
    virtual void SetListener(std::unique_ptr<Listener> uniqueListener) = 0;

    /**
     * @brief Add the build options to the simulator
     * 
     * @param buildOptions 
     */
    virtual void AddBuildOptions(const std::vector<BuildOptions>& buildOptions) = 0;

    /**
     * @brief Load the configuration for the simulator
     * 
     * @param simulatorVersion 
     */
    virtual void LoadConfiguration(const std::string& simulatorVersion) = 0;

    /**
     * @brief Write the configuration to a file
     * 
     * @param configFileName 
     */
    virtual void WriteToConfiguration(std::string configFileName) = 0;

    /**
     * @brief Load the parameters for the simulator
     * 
     * @param parameter 
     */
    virtual void LoadParameters(std::vector<Parameter>& parameter) = 0;

    /**
     * @brief Load the metrics for the simulator
     * 
     * @param metrics 
     */
    virtual void LoadMetrics(std::vector<Metrics>& metrics) = 0;

    /**
     * @brief Run the simulation
     * 
     */
    virtual void RunSimulation() = 0;    
};

#endif
