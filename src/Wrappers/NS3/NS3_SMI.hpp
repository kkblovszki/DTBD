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


    /**
     * @brief Set the Listener object
     * Using this function which takes two parameters @param uniqueListener
     * the simulator can set the listener that is used by the simulator, the unique listener is the 
     * listener that is created in the constructor of a scenario to be Set to the specific simulator instance.
     * @param uniqueListener The created listener from scenario constructor
     */
    virtual void SetListener(std::unique_ptr<Listener> uniqueListener) override {
        activeSimulatorListener = std::move(uniqueListener); uniqueListener.reset(); 
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
     */
    /*virtual void SetListener(std::unique_ptr<Listener> uniqueListener, std::unique_ptr<Listener> simulatorUniqueListener) override {
        simulatorUniqueListener = std::move(uniqueListener); uniqueListener.reset(); 
    }*/

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