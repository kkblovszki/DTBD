#include "NS3_SMI.hpp"

/**
 * @todo:
 * 
 * When creating a new simulator, the following steps need to be taken:
 * - Run constructor:
 *      
 *      - load the APIFunctionPassThrough from the NS3_config.yaml file
 * - Return a NS3_mockup_interface object from the createSimulator function
 * 
 * When the LoadConfiguration function is called, the following steps need to be taken:
 * - load the persistent data from the NS3_config.yaml file
 *          - Get the supported parameters
 * 
 * - Crosscheck the supported parameters from the simulator with the inputted parameters
 * - If the parameters are supported, then pass them to the simulator else throw an error saying that the specific parameter(s) are not supported
 * - It then creates a list of the supported metrics and parameters from the simulator
 * 
 * When the LoadMetrics function is called, the following steps need to be taken:
 * - Convert the standardized metrics to the simulator specific metrics types 
 * 
 * When the LoadParameters function is called, the following steps need to be taken:
 * - Get the inputted parameters from the benchmark yaml file
 * - Convert the standardized parameters to the simulator specific parameters types i.e. BuildOptions Type
 * 
 * When the ParseToNS3CommandLine function is called, the following steps need to be taken:
 * - Parse the inputted parameters to an NS3 command line string for building the simulation  
 *  
 * When RunSimulation is called, the following steps need to be taken:
 * - Run the parsing function to parse the inputted parameters to an NS3 command line string for building the simulation
 * - Set up a filestream to read the output from the simulation
 * - Run the simulation
 * - Read the output from the simulation
 * 
 */

/**
 * @brief Construct a new ns3 mockup interface::ns3 mockup interface object
 * 
 */
NS3_mockup_interface::NS3_mockup_interface(){

    simulatorInfo = SimulatorInfo();
    APIFunctionPassThrough = std::map<std::string, int>();

    YAML::Node config = YAML::LoadFile("PersistentData.yaml");
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


NS3_mockup_interface::~NS3_mockup_interface(){};

/**
 * @brief 
 * @return void*
 */
extern "C" void* NS3_mockup_interface::createSimulator() {
    return new NS3_mockup_interface();
};

/**
 * @brief Load the configuration from the benchmark
 * @param NS3ScenarioConfig Single NS3 scenario configuration mapped from the Benchmark class
 */
void NS3_mockup_interface::LoadConfiguration(YAML::Node& NS3ScenarioConfig) {
    //load the persistent data from specific NS3 yaml file, insert it into the SimulatorInfo simulatorInfo variable
    //load the APIFunctionPassThrough from specific NS3 yaml file, insert it into the std::map<std::string,int> APIFunctionPassThrough variable

    std::stringstream command;
    std::vector<std::string> options;

    const auto& scenario = NS3ScenarioConfig["Simulator"]["Scenario"];

    // Add program name
    command << "./ns3 run '" << scenario["simulator"].as<std::string>() << "' ";

    // Add required arguments
    command << "--topology-file-path=" << scenario["required"]["topology-file-path"].as<std::string>() << " ";
    command << "--traffic-file-path=" << scenario["required"]["traffic-file-path"].as<std::string>() << " ";

    // Add optional arguments
    if (!scenario["optional"].IsNull()) {
        command << "--optional=" << scenario["optional"].as<std::string>() << " ";
    }

    // Add build options
    if (config["Simulator"]["Scenario"]["BuildOptions"]) {
        const auto& buildOptions = config["Simulator"]["Scenario"]["BuildOptions"];
        for (const auto& it : buildOptions) {
            options.push_back("--" + it.second.as<std::string>() + "-" + it.first.as<std::string>());
        }
    }

    // Add parameters
    if (config["Simulator"]["Scenario"]["Parameters"]) {
        const auto& parameters = config["Simulator"]["Scenario"]["Parameters"];
        for (const auto& it : parameters) {
            options.push_back("--" + it.second.as<std::string>() + "-" + it.first.as<std::string>() );
        }
    }

    // Sort options alphabetically for consistency
    std::sort(options.begin(), options.end());

    // Add options to command
    for (const auto& option : options) {
        command << option << " ";
    }
    
    //debug
    std::cout << command.str() << std::endl;
    
};

void NS3_mockup_interface::WriteToConfiguration(std::string configFileName){};

/**
 * @brief 
 * Set the library handle for the simulator
 * @param libraryHandle 
 */
void NS3_mockup_interface::setLibraryHandle(void* libraryHandle) {
    auto libHandle = static_cast<void*>(libraryHandle);
    ns3LibHandler = libHandle;
};

/**
 * @brief
 * @param parameter
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
 */
void NS3_mockup_interface::LoadMetrics(std::map<std::string, Metrics>& metrics) {
    
    //Check if the metrics are supported by the simulator
    for(auto it = metrics.begin(); it != metrics.end(); ++it){
        //check if its supported and that the type inputed is matching the type supported by the simulator
        if(std::find(simulatorInfo.supportedMetrics.begin(), simulatorInfo.supportedMetrics.end(), it->first) == simulatorInfo.supportedMetrics.end()){
            std::cerr << "Metric: " << it->first << " is not supported by the simulator" << std::endl;
        }else{
            //if the metric is supported by the simulator, then add it to the metrics map
            Metrics metric = Metrics(it->first, it->second.unit);
            metrics.insert(std::pair<std::string, Metrics>(it->first, metric));
        }   
    }
};


/**
 * @brief
 * Run the parsing function to parse the inputted parameters to an NS3 command line string for building the simulation
 * Set up a filestream which can capture the output from the simulation -out files stream and redirect the the listener
 * Run the simulation through command line the using the command line string 
 * @param parameters 
 * @return std::string 
 */
void NS3_mockup_interface::RunSimulation(){
    //Run the parsing function to parse the inputted parameters to an NS3 command line string for building the simulation
    //std::string commandLine = ParseToNS3CommandLine(parameters, buildoptions);

    namespace fs = std::filesystem; 
    fs::path tempPath = fs::temp_directory_path()/"output.txt";

    std::ofstream outputFile(tempPath);

    //redirect the output to the file
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    std::cout.rdbuf(outputFile.rdbuf());

    //Run the simulation through command line the using the command line string
    activeSimulatorListener->OnSimulationStart(metrics);

    system(commandLine.c_str());

    std::thread ThreadUpdate(UpdateListener);

    //Wait for thread to finish
    ThreadUpdate.join();

    activeSimulatorListener->OnSimulationEnd();

    //Cleanup
    std::cout.rdbuf(oldCoutStreamBuf); //Reset the cout stream buffer
    fs::remove(tempPath); //remove the file
};

/**
 * @brief 
 * basic function which parses the parameters to an NS3 command line string for building the simulation
 * and the build options to an NS3 command line string for building the simulation
 * @param parameter 
 * @return std::string 
 */
void NS3_mockup_interface::ParseToNS3CommandLine(std::map<std::string, Parameter>& parameter, std::map<std::string, BuildOptions>& buildOptions){
    
    std::string ParamsCMDstring = "ns3 ";
    std::string BuildCMDstring = "ns3 ";

    //Parse the build options to an NS3 command line string for building the simulation
    for(auto it = buildOptions.begin(); it != buildOptions.end(); ++it){
        BuildCMDstring += "--" + it->first + "=" + it->second.buildOptionValue + " ";
    }

    //Parse the parameters to an NS3 command line string for building the simulation
    for(auto it = parameter.begin(); it != parameter.end(); ++it){
        ParamsCMDstring += "--" + it->first + "=" + it->second.defaultParameter + " ";
    }

    CL_Parameters = ParamsCMDstring;
    CL_BuildOptions = BuildCMDstring;
};



void NS3_mockup_interface::GetRuntimeData(){};

