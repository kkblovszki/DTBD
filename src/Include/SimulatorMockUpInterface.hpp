#ifndef SIMULATOR_MOCKUP_INTERFACE_HPP
#define SIMULATOR_MOCKUP_INTERFACE_HPP

#include "core.Types.hpp"
#include "AbstractListener.hpp"

class SimulatorMockUpInterface
{
protected:
     SimulatorInfo simulatorInfo; //Contains all the simulator information.

private:
    std::map<std::string, int> APIFunctionPassThrough;
    std::unique_ptr<Listener> activeSimulatorListener;

public:
    SimulatorMockUpInterface(){};
    ~SimulatorMockUpInterface(){};
    //SimulatorMockUpInterface(SimulatorInfo specifiedSimulator, std::map<std::string,int> specifiedAPIFunction);
   
    //virtual void createSimulator(SimulatorInfo specifiedSimulator, std::map<std::string,int> specifiedAPIFunction);

    virtual void setLibraryHandle(void* libraryHandle) = 0;
    virtual void SetListener(std::unique_ptr<Listener> uniqueListener) = 0;
    virtual void AddBuildOptions(const std::vector<BuildOptions>& buildOptions) = 0;
    virtual SimulatorInfo GetSimulatorInfo() = 0;
    
    virtual void LoadConfiguration(const std::string& simulatorVersion) = 0;
    virtual void WriteToConfiguration(std::string configFileName) = 0;
    virtual void LoadParameters(std::vector<Parameter>& parameter) = 0;
    virtual void LoadMetrics(std::vector<Metrics>& metrics) = 0;
    virtual void RunSimulation() = 0;

    /*virtual void GetRuntimeData() = 0;

    std::vector<std::size_t> GetSimulationResults(){
        return std::vector<std::size_t>();
    };*/
    
};

#endif
