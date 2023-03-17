#include "NS3_SMI.hpp"

NS3_mockup_interface::NS3_mockup_interface(){}

NS3_mockup_interface::~NS3_mockup_interface(){}

extern "C" void* NS3_mockup_interface::createSimulator() {
    //auto simulator = new NS3_mockup_interface();
    //simulator->simulatorInfo = SimulatorInfo(specifiedSimulator.simulatorName = "NS3",
    //                                         specifiedSimulator.simulatorVersion = "3.29",
    //                                         specifiedSimulator.nativeOutputType = "ns3::Packet",
    //                                         specifiedSimulator.functions = {},
    //                                         specifiedSimulator.parameters = {});
    return new NS3_mockup_interface();
};

void NS3_mockup_interface::setLibraryHandle(void* libraryHandle) {
    auto libHandle = static_cast<void*>(libraryHandle);
    ns3LibHandler = libHandle;
};

void NS3_mockup_interface::LoadConfiguration(std::string configFileName) {
    
};

void NS3_mockup_interface::WriteToConfiguration(std::string configFileName) {

};

void NS3_mockup_interface::LoadProblem(std::map<std::string, std::string> CoreProblemCallback()) {

};

void NS3_mockup_interface::LoadMetrics() {

};

void NS3_mockup_interface::RunSimulation(){
    activeSimulatorListener->OnSimulationEnd();
};

void NS3_mockup_interface::GetRuntimeData(){

};

