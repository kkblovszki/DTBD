#ifndef SIMULATOR_MOCKUP_INTERFACE_HPP
#define SIMULATOR_MOCKUP_INTERFACE_HPP

#include "core.Types.hpp"
#include "AbstractListener.hpp"
#include <functional>

/**
    @page   Simulator-Mockup-Interface Simulator Mockup Interface

    @brief This class is an mockup interface for a simulator. It contains all the functions that a simulator should implement.

    @section  what-is-the-smi  What is the SMI?

    The term Simulator mock-up interface is coined by the authors of this framework and is defined as follows:
    in the context of this thesis, we will introduce a new term Simulator Mock-up Interface .
    The Simulator Mock-up Interface in software design represents a standardised blueprint that
    facilitates the connection of different simulators to a common interface. This term defines a
    unified protocol, dictating the methods and properties that a class must implement to operate
    a simulator within a consistent environment. Its purpose is to enable systematic interaction
    with one or multiple simulators through standardised method of connection, hence promoting
    interoperability and simplifying the integration process, of new and old simulators. It can be
    used in connection with a simulator name to describe the actual SMI implementation for said
    simulator. Examples of this would be OpenSIM SMI, NS-3 SMI and Alchemist SMI.
    
    @details The SimulatorMockUpInterface is an interface for the simulator. It contains all the functions that a simulator should implement.
    The class is an abstract class, which means that it cannot be instantiated. It is used to create a common interface for the simulators.
    The class contains a map of strings to functions, which can be used to implement a DSL language. 

    SimulatorMockUpInterface have the following functions:
    @li SimulatorMockUpInterface::SimulatorMockUpInterface()
    @li SimulatorMockUpInterface::~SimulatorMockUpInterface()
    @li SimulatorMockUpInterface::GetSimulatorInfo()
    @li SimulatorMockUpInterface::SetLibraryHandle(void* libraryHandle)
    @li SimulatorMockUpInterface::SetListener(std::unique_ptr<Listener> newListener)
    @li SimulatorMockUpInterface::LoadConfiguration(std::string simulatorVersion)
    @li SimulatorMockUpInterface::AddBuildOptions(std::vector<BuildOptions> buildOptions)
    @li SimulatorMockupInterface::WriteToConfiguration(std::string configFileName)
    @li SimulatorMockUpInterface::LoadParameters(std::vector<Parameter> parameter)
    @li SimulatorMockUpInterface::LoadMetrics(std::vector<Metrics> metrics)
    @li SimulatorMockUpInterface::RunSimulation()

    For instantiation of SMI's based on @ref Simulator-Mockup-Interface @see SimulatorCreator
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