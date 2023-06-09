#ifndef NS3_INTERFACE_HPP
#define NS3_INTERFACE_HPP

#include "../include/SimulatorMockUpInterface.hpp"
#include <./yaml-cpp/yaml.h>
#include <fstream>
#include <thread>
#include <chrono>
#include <filesystem>
#include <utility>
#include <functional>

//#include <pty.h> for forkpty but not implemented to use it yet.

/**
 * @brief NS3_mockup_interface is a class that implements the SimulatorMockUpInterface.
 * 
 * @page NS3_mockup_interfacePage NS3_mockup_interface
 * 
 * @section NS3_mockup_interface
 * 
 * This class is used to create a NS3 simulator instance, and to run a simulation with it.
 * 
 * @details This class is used to create a NS3 simulator instance, and to run a simulation with it.
 * 
 */
class NS3_mockup_interface : SimulatorMockUpInterface {    
private:
    const std::string SMIPath = SMI_PATH; //contains the path to the SMI folder.
    const std::string ResultPath = RESULTS_PATH; //contains the path to the NS3 folder.
    std::map<std::string, std::function< std::unique_ptr<void()>() >> APIFunctionPassThrough;  //contains the API functions that can be used from simulator.
    std::unique_ptr<Listener> activeSimulatorListener; //contains the listener that is used by the simulator.
    std::vector<Metrics> NS3metrics;            //contains the metrics that are used by the simulator.
    std::vector<BuildOptions> NS3buildOptions;  //contains the build options that are used by the simulator.
    std::vector<Parameter> NS3parameters;       //contains the parameters that are used by the simulator.
    std::string PersistentConfigFilePath;       //contains the path to the config file that is used by the simulator.
    std::shared_ptr<void> ns3LibHandler; // contains the handler to the individual ns3 library instance.

    /**
     * @brief 
     * Command line strings build inside the respective 
     * @ref LoadParameter function and used in the @ref RunSimulation function
     */
    std::string CL_BuildOptions; //contains the build options that are used by the simulator, in a string.
    std::string CL_Parameters; //contains the parameters that are used by the simulator, in a string.

    /**
     * @brief 
     * Parses the given parameters and build options into a string /ref CL_BuildOptions and /ref CL_Parameters
     */
    void ParseToNS3CommandLine();

public:
    NS3_mockup_interface();
    ~NS3_mockup_interface();

    void* createSimulator();

    SimulatorInfo GetSimulatorInfo() override;

    /**
     * @brief Set the Listener object
     * Using this function which takes two parameters @param uniqueListener
     * the simulator can set the listener that is used by the simulator, the unique listener is the 
     * listener that is created in the constructor of a scenario to be Set to the specific simulator instance.
     * @param uniqueListener The created listener from scenario constructor
     */
    virtual void SetListener(std::unique_ptr<Listener> uniqueListener) override {
        activeSimulatorListener = std::move(uniqueListener); 
        uniqueListener.reset(); 
    }
    
    /**
     * @brief Add Build Options to the simulator
     * 
     * @param buildOptions 
     */
    virtual void AddBuildOptions(const std::vector<BuildOptions>& buildOptions) override;

    /**
     * @brief Set the Library Handle object
     * 
     * @param libraryHandle 
     */
    virtual void setLibraryHandle(std::shared_ptr<void> libraryHandle) override;
    
    /**
     * @brief Load the configuration file of the simulator.
     * 
     * @param simulatorVersion 
     */
    virtual void LoadConfiguration(const std::string& simulatorVersion) override; //loads the configuration file of the simulator.
    
    /**
     * @brief Write the configuration file of the simulator.
     * 
     * @param configFileName 
     */
    virtual void WriteToConfiguration(std::string configFileName) override;

    /**
     * @brief Load the parameters into the simulator.
     * 
     * @param parameter 
     */
    virtual void LoadParameters(std::vector<Parameter>& parameter) override;
    
    /**
     * @brief Load the metrics into the simulator.
     * 
     * @param metrics 
     */
    virtual void LoadMetrics(std::vector<Metrics>& metrics) override;
    
    /**
     * @brief Run the simulation.
     */
    virtual void RunSimulation() override;
    
};

#endif