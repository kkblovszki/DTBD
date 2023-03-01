#ifndef NS3_INTERFACE_HPP
#define NS3_INTERFACE_HPP
#include "./include/SimulatorMockUpInterface.hpp"

class NS3Interface : SimulatorMockUpInterface {
private:
    SimulatorInfo simulator;
    std::map<std::string,int> APIFunctionPassThrough;
    std::unique_ptr<Listener> activeSimulatorListener;
public:
    NS3Interface();
    ~NS3Interface();

    virtual void LoadConfiguration(std::string configFileName) override;
    virtual void WriteToConfiguration(std::string configFileName) override;
    virtual void LoadProblem(std::map<std::string, std::string> CoreProblemCallback()) override;
    virtual void LoadMetrics() override;
    virtual void RunSimulation() override;
    virtual void GetRuntimeData() override;
    std::vector<std::size_t> GetSimulationResults(){};

};

#endif