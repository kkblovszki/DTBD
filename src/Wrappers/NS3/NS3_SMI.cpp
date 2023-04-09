#include "NS3_SMI.hpp"

/**
 * @todo:
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
 */

/**
 * @brief Construct a new ns3 mockup interface::ns3 mockup interface object
 */
NS3_mockup_interface::NS3_mockup_interface(){
    LoadConfiguration(); // Load the configuration from the NS3_config.yaml file
    activeSimulatorListener = nullptr; // Set the listener to null
    ns3LibHandler = nullptr; // Set the library handler to null
}

NS3_mockup_interface::~NS3_mockup_interface(){};

/**
 * @brief Returns an instance of the NS3 simulator interface
 * @return void*
 */
extern "C" void* NS3_mockup_interface::createSimulator() {
    return new NS3_mockup_interface();
};

/**
 * @brief Load the configuration from the benchmark
 * @param NS3ScenarioConfig Single NS3 scenario configuration mapped from the Benchmark class
 */
void NS3_mockup_interface::LoadConfiguration() {

    simulatorInfo = SimulatorInfo();
    APIFunctionPassThrough = std::map<std::string, int>();

    namespace fs = std::filesystem;
    fs::path configPath = fs::current_path() / "PersistentData.yaml";

    YAML::Node config = YAML::LoadFile(configPath.string());
    YAML::Node persistentData = config["persistentData"];
    YAML::Node APIFunctionPassThrough = config["APIFunctionPassThrough"];

    /*Store the individual information in the simulatorInfo variables*/ 
    simulatorInfo.simulatorName = persistentData["simulatorName"].as<std::string>();
    simulatorInfo.simulatorVersion = persistentData["simulatorVersion"].as<std::string>();

    /*Store the supported parameters for the simulator SMI from the persistentData*/
    for (YAML::const_iterator it = persistentData["supportedParameters"].begin(); it != persistentData["supportedParameters"].end(); ++it){
        //Get the name of each individual supportedParameters and add it to the list of supportedParameters for the simulatorInfo.SupportedParameters
        //simulatorInfo.supportedParameters.push_back(it->first.as<std::string>());
        simulatorInfo.supportedParameters.push_back(it->as<std::string>());
    }
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
void NS3_mockup_interface::LoadParameters(std::vector<Parameter>& parameter) {
    for(auto it = parameter.begin(); it != parameter.end(); ++it){
        if(std::find(simulatorInfo.supportedParameters.begin(), simulatorInfo.supportedParameters.end(), (it->name)) == simulatorInfo.supportedParameters.end()){
            std::cerr << "Parameter: " << (it->name) << " is not supported by the simulator" << std::endl;
        }else{
            //if the metric is supported by the simulator, then add it to the metrics map
            NS3parameters.emplace_back(*it);
        }
    }
};

/**
 * @brief 
 * The LoadMetrics function is used to crosscheck the supported metrics from the 
 * simulator with the metrics that are inputted in the benchmark yaml config file, 
 * and parsed to the individual scenarios where the variable called is metrics.
 */
void NS3_mockup_interface::LoadMetrics(std::vector<Metrics>& metrics) {
    //Check if the metrics are supported by the simulator
    for(auto it = metrics.begin(); it != metrics.end(); ++it){
        //check if its supported and that the type inputed is matching the type supported by the simulator
        /*if(std::find(simulatorInfo.supportedMetrics.begin(), simulatorInfo.supportedMetrics.end(), *it) == simulatorInfo.supportedMetrics.end()){
            std::cerr << "Metric: " << (it->name) << " is not supported by the simulator" << std::endl;
        }else{
            //if the metric is supported by the simulator, then add it to the metrics map
            NS3metrics.emplace_back(*it);
        }*/
    }
};

/**
 * @brief 
 * basic function which parses the parameters to an NS3 command line string for building the simulation
 * and the build options to an NS3 command line string for building the simulation
 * @param parameter 
 * @return std::string 
 */
void NS3_mockup_interface::ParseToNS3CommandLine(std::vector<BuildOptions>& buildOptions){
    std::string ParamsCMDstring = "./ns3 build "; //possible point of failure.
    std::string BuildCMDstring = "./ns3 run "; //possible point of failure.
    
    //Parse the build options to an NS3 command line string for building the simulation
    for(auto it = buildOptions.begin(); it != buildOptions.end(); ++it){
        BuildCMDstring += "--" + it->buildOption + "=" + it->buildOptionValue + " ";
    }

    //Parse the parameters to an NS3 command line string for building the simulation
    for(auto it = NS3parameters.begin(); it != NS3parameters.end(); ++it){
        ParamsCMDstring += "--" + (it->name) + "=" + (it->defaultParameter) + " ";
    }

    CL_Parameters = ParamsCMDstring;
    CL_BuildOptions = BuildCMDstring;
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
    //std::string commandLine = ParseToNS3CommandLine(buildoptions);

    auto currentTime = std::chrono::system_clock::now();
    std::string currentTimeInHourMinSec = 
        std::to_string(std::chrono::duration_cast<std::chrono::hours>(currentTime.time_since_epoch()).count()) + 
        std::to_string(std::chrono::duration_cast<std::chrono::minutes>(currentTime.time_since_epoch()).count()) + 
        std::to_string(std::chrono::duration_cast<std::chrono::seconds>(currentTime.time_since_epoch()).count());

    std::string fileOutput = simulatorInfo.simulatorName + "_" + currentTimeInHourMinSec + ".txt";

    CL_Parameters += " > " + fileOutput + " 2>&1";

    activeSimulatorListener->SimulationStart();

    #ifdef UNIX
         //First we build/configure the simulation
        system(CL_BuildOptions.c_str());
        //Then we run the simulation
        system(CL_Parameters.c_str());
    #endif

    #ifdef WINDOWS
        //Use wslapi.h to run the simulation
    #endif

    std::string smiPath = SMI_PATH;
    std::string changeDirectory = "cd "+ smiPath;

     //First we build/configure the simulation
    system(CL_BuildOptions.c_str());

    //Then we run the simulation
    system(CL_Parameters.c_str());
   

    activeSimulatorListener->SimulationEnd();

    //namespace fs = std::filesystem;
    //fs::path tempPath = fs::temp_directory_path()/"output.txt";
    //
    //std::ofstream outputFile(tempPath);
    //
    ////redirect the output to the file
    //std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    //std::cout.rdbuf(outputFile.rdbuf());
    //
    //Run the simulation through command line the using the command line string
    //activeSimulatorListener->OnSimulationStart(NS3metrics);

    //First we build the simulation
    //system(CL_BuildOptions.c_str());

    //Then we run the simulation
    //system(CL_Parameters.c_str());

    //std::thread ThreadUpdate(UpdateListener);
    //Wait for thread to finish
    //ThreadUpdate.join();

    //activeSimulatorListener->OnSimulationEnd();

    //Cleanup
    //std::cout.rdbuf(oldCoutStreamBuf); //Reset the cout stream buffer
    //fs::remove(tempPath); //remove the file
};



void NS3_mockup_interface::GetRuntimeData(){};

