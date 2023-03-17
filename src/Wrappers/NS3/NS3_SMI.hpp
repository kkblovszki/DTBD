#ifndef NS3_INTERFACE_HPP
#define NS3_INTERFACE_HPP
#include "../include/SimulatorMockUpInterface.hpp"

class NS3_mockup_interface : SimulatorMockUpInterface {
private:

    SimulatorInfo simulatorInfo;
    std::map<std::string,int> APIFunctionPassThrough;
    std::unique_ptr<Listener> activeSimulatorListener;
    void* ns3LibHandler;

public:
    NS3_mockup_interface();
    ~NS3_mockup_interface();

    void* createSimulator();

    virtual void setLibraryHandle(void* libraryHandle) override;
    virtual void LoadConfiguration(std::string configFileName) override;
    virtual void WriteToConfiguration(std::string configFileName) override;
    virtual void LoadProblem(std::map<std::string, std::string> CoreProblemCallback()) override;
    virtual void LoadMetrics() override;
    virtual void RunSimulation() override;
    virtual void GetRuntimeData() override;
    std::vector<std::size_t> GetSimulationResults(){return std::vector<std::size_t>();};

};

#endif