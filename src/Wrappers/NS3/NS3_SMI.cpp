#include "NS3_SMI.hpp"


/**
 * @brief Construct a new ns3 mockup interface::ns3 mockup interface object
 * 
 */
NS3_mockup_interface::NS3_mockup_interface(){
    //load the persistent data from specific NS3 yaml file, insert it into the SimulatorInfo simulatorInfo variable
    //load the APIFunctionPassThrough from specific NS3 yaml file, insert it into the std::map<std::string,int> APIFunctionPassThrough variable

    simulatorInfo = SimulatorInfo();
    APIFunctionPassThrough = std::map<std::string, int>();

    YAML::Node config = YAML::LoadFile("NS3_config.yaml");
    YAML::Node persistentData = config["persistentData"];
    YAML::Node APIFunctionPassThrough = config["APIFunctionPassThrough"];


    /*Store the individual information in the simulatorInfo variables*/ 
    simulatorInfo.simulatorName = persistentData["simulatorName"].as<std::string>();
    simulatorInfo.simulatorVersion = persistentData["simulatorVersion"].as<std::string>();

    /*Store the supported parameters for the simulator SMI from the persistentData*/
    for (YAML::const_iterator it = persistentData["supportedParameters"].begin(); it != persistentData["supportedParameters"].end(); ++it){
        simulatorInfo.supportedParameters.push_back(it->as<std::string>());
    }

    activeSimulatorListener = nullptr;
    ns3LibHandler = nullptr;
}

extern "C" void* NS3_mockup_interface::createSimulator() {
    return new NS3_mockup_interface();
};

NS3_mockup_interface::~NS3_mockup_interface(){};

void NS3_mockup_interface::LoadConfiguration(std::string configFileName) {};

void NS3_mockup_interface::WriteToConfiguration(std::string configFileName) {};

void NS3_mockup_interface::setLibraryHandle(void* libraryHandle) {
    auto libHandle = static_cast<void*>(libraryHandle);
    ns3LibHandler = libHandle;
};

/**
 * @brief 
 * Based on the 
 * @param CoreProblemCallback 
 */
void NS3_mockup_interface::LoadParameters(std::map<std::string, Parameter>& parameter) {
    /**/
    for(auto it = parameter.begin(); it != parameter.end(); ++it){
        if(std::find(simulatorInfo.supportedParameters.begin(), simulatorInfo.supportedParameters.end(), it->first) == simulatorInfo.supportedParameters.end()){
            std::cerr << "Parameter: " << it->first << " is not supported by the simulator" << std::endl;
        }
    }
};


/**
 * @brief 
 * The LoadMetrics function is used to crosscheck the supported metrics from the 
 * simulator with the metrics that are inputted in the benchmark yaml config file, 
 * and parsed to the individual scenarios where the variable called is metrics.
 * The input o
 */
void NS3_mockup_interface::LoadMetrics(std::map<std::string, Metrics>& metrics) {
    //Check if the metrics are supported by the simulator
    for(auto it = metrics.begin(); it != metrics.end(); ++it){
        if(std::find(simulatorInfo.supportedMetrics.begin(), simulatorInfo.supportedMetrics.end(), it->first) == simulatorInfo.supportedMetrics.end()){
            std::cerr << "Metric: " << it->first << " is not supported by the simulator" << std::endl;
        }
    }
};


void NS3_mockup_interface::RunSimulation(){


};

void NS3_mockup_interface::GetRuntimeData(){};

