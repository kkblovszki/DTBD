#include "NS3_SMI.hpp"

NS3_mockup_interface::NS3_mockup_interface(){
    //load the persistent data from specific NS3 yaml file, insert it into the SimulatorInfo simulatorInfo variable
    //load the APIFunctionPassThrough from specific NS3 yaml file, insert it into the std::map<std::string,int> APIFunctionPassThrough variable

    simulatorInfo = SimulatorInfo();
    APIFunctionPassThrough = std::map<std::string, int>();

    YAML::Node config = YAML::LoadFile("NS3_config.yaml");
    YAML::Node persistentData = config["persistentData"];
    YAML::Node APIFunctionPassThrough = config["APIFunctionPassThrough"];


    activeSimulatorListener = nullptr;
    ns3LibHandler = nullptr;
}

NS3_mockup_interface::~NS3_mockup_interface(){}

extern "C" void* NS3_mockup_interface::createSimulator() {
    
    return new NS3_mockup_interface();
};

void NS3_mockup_interface::setLibraryHandle(void* libraryHandle) {
    auto libHandle = static_cast<void*>(libraryHandle);
    ns3LibHandler = libHandle;
};

void NS3_mockup_interface::LoadConfiguration(std::string configFileName /*Yaml::node Config*/) {
};

void NS3_mockup_interface::WriteToConfiguration(std::string configFileName) {

};

void NS3_mockup_interface::LoadProblem(std::map<std::string, std::string> CoreProblemCallback()) {

};

void NS3_mockup_interface::LoadMetrics() {

};

void NS3_mockup_interface::RunSimulation(){ 

};

void NS3_mockup_interface::GetRuntimeData(){
    
};

