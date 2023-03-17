#ifndef SIMULATOR_MOCKUP_INTERFACE_HPP
#define SIMULATOR_MOCKUP_INTERFACE_HPP

#include "core.Types.hpp"
#include "AbstractListener.hpp"

class SimulatorMockUpInterface
{
private:
    std::map<std::string, int> APIFunctionPassThrough;
    std::unique_ptr<Listener> activeSimulatorListener;

public:
    SimulatorMockUpInterface(){};
    ~SimulatorMockUpInterface(){};
    //SimulatorMockUpInterface(SimulatorInfo specifiedSimulator, std::map<std::string,int> specifiedAPIFunction);
    SimulatorInfo simulator;
    //virtual void createSimulator(SimulatorInfo specifiedSimulator, std::map<std::string,int> specifiedAPIFunction);

    virtual void setLibraryHandle(void* libraryHandle) = 0;
    virtual void SetListener(std::unique_ptr<Listener> uniqueListener) = 0;
    virtual void LoadConfiguration(std::string configFileName) = 0;
    virtual void WriteToConfiguration(std::string configFileName) = 0;
    virtual void LoadProblem(std::map<std::string, std::string> CoreProblemCallback()) = 0;
    virtual void LoadMetrics() = 0;
    virtual void RunSimulation() = 0;
    virtual void GetRuntimeData() = 0;
    std::vector<std::size_t> GetSimulationResults(){
        return std::vector<std::size_t>();
    };
    
};

#endif
