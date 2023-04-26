#ifndef NS3_INTERFACE_HPP
#define NS3_INTERFACE_HPP

#include "../include/SimulatorMockUpInterface.hpp"
#include <./yaml-cpp/yaml.h>
#include <fstream>
#include <thread>
#include <chrono>
#include <filesystem>
#include <utility>
#include <pty.h>

#ifdef DEBUG
    #include <source_location>
#endif

/*
#ifdef defined (__UNIX__) || defined (__UNIX) || defined (__APPLE__) ||  defined (__MACH__) 
    #include <libutil>
#elif defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #include wslapi.h
#endif*/

class NS3_mockup_interface : SimulatorMockUpInterface {    
private:
    const std::string SMIPath = SMI_PATH; //contains the path to the SMI folder.
    const std::string ResultPath = RESULTS_PATH; //contains the path to the NS3 folder.
    std::map<std::string,int> APIFunctionPassThrough;  //contains the API functions that can be used from simulator.
    std::unique_ptr<Listener> activeSimulatorListener; //contains the listener that is used by the simulator.
    std::vector<Metrics> NS3metrics;            //contains the metrics that are used by the simulator.
    std::vector<BuildOptions> NS3buildOptions;  //contains the build options that are used by the simulator.
    std::vector<Parameter> NS3parameters;       //contains the parameters that are used by the simulator.
    std::string PersistentConfigFilePath;       //contains the path to the config file that is used by the simulator.
    void* ns3LibHandler; // contains the handler to the individual ns3 library instance.

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

    /*void UpdateListener(std::ifstream& outputFileStream){
        std::string line;
        if(outputFileStream.is_open()){
            while(getline(outputFileStream, line)){
                activeSimulatorListener->OnSimulationUpdate(line);
                std::this_thread::sleep_for(std::chrono::nanoseconds(100));
            }
            outputFileStream.close();
        }
    }*/

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


    //universal function to set the listener idea
    /**
     * @brief Set the Listener object
     * Using this function which takes two parameters @param uniqueListener and @param simulatorUniqueListener
     * the simulator can set the listener that is used by the simulator, the unique listener is the 
     * listener that is created in the constructor of a scenario while the simulatorUniqueListener 
     * is the listener that is used by the simulator.
     * @param uniqueListener The created listener
     * @param simulatorUniqueListener The listener that is used by the simulator
     *
    */
    /*virtual void SetListener(std::unique_ptr<Listener> uniqueListener, std::unique_ptr<Listener> simulatorUniqueListener) override {
        simulatorUniqueListener = std::move(uniqueListener); uniqueListener.reset(); 
    }*/
    
    virtual void AddBuildOptions(const std::vector<BuildOptions>& buildOptions) override;
    virtual void setLibraryHandle(void* libraryHandle) override;
    virtual void LoadConfiguration(const std::string& simulatorVersion) override; //loads the configuration file of the simulator.
    virtual void WriteToConfiguration(std::string configFileName) override;
    virtual void LoadParameters(std::vector<Parameter>& parameter) override;
    virtual void LoadMetrics(std::vector<Metrics>& metrics) override;
    virtual void RunSimulation() override;
    
};

#endif