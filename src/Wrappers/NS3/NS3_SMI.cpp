#include "NS3_SMI.hpp"

////////////////////////////
/// @file NS3_SMI.cpp
/// @brief NS3_SMI.cpp contains the implementation of the NS3 simulator interface
///
/// @author:  Mikkel Silkeborg
/// @version: 1.0
/// @date:    17-03-2023
/// @note:   This file contains the implementation of the NS3 simulator interface, only supported on Linux
/// @desc:   {This file contains the implementation of the NS3 simulator interface.
///           The interface doesn't currently clean-up after itself during copy of the simulation files.}
////////////////////////////

/**
 * @brief Construct a new ns3 mockup interface::ns3 mockup interface object
 */
NS3_mockup_interface::NS3_mockup_interface(){
    activeSimulatorListener = nullptr; // Set the listener to null
    ns3LibHandler = nullptr; // Set the library handler to null
}

/**
 * @brief Destroy the ns3 mockup interface::ns3 mockup interface object
 */
NS3_mockup_interface::~NS3_mockup_interface(){};

/**
 * @brief Returns an instance of the NS3 simulator interface
 * @return void*
 */
extern "C" void* NS3_mockup_interface::createSimulator() {
    return new NS3_mockup_interface();
};

/**
 * @brief Return the simulator information
 * @return SimulatorInfo 
 */
SimulatorInfo NS3_mockup_interface::GetSimulatorInfo() {
    return simulatorInfo; //Return a copy of the simulatorInfo
}

/**
 * @brief Add build options to the simulator
 * @param buildOptions 
 */
void NS3_mockup_interface::AddBuildOptions(const std::vector<BuildOptions>& buildOptions) {
    this->NS3buildOptions = buildOptions;
}

/**
 * @brief Load the configuration from the benchmark
 * @param NS3ScenarioConfig Single NS3 scenario configuration mapped from the Benchmark class
 */
void NS3_mockup_interface::LoadConfiguration(const std::string& simulatorVersion) {
    
    //before filling out simulator info, we use the version to check if they match 
    const std::string simulatorSpecificPath = "/NS3-SMI";
    const std::string simulatorName = "/ns-";
    const std::string PersistentDataFileName = "/PersistentData.yaml";

    PersistentConfigFilePath = SMIPath + simulatorSpecificPath + simulatorName + simulatorVersion + PersistentDataFileName;
    
    #ifdef DEBUG
        std::cout << "Loading configuration from: " << PersistentConfigFilePath << std::endl;
    #endif

    ////Load the configuration file
    YAML::Node persistentData = YAML::LoadFile(PersistentConfigFilePath);

    std::string SimulatorName;

    /*Store the individual information in the simulatorInfo variables*/ 
    try{
        SimulatorName = persistentData["SimulatorName"].as<std::string>();
    } catch (YAML::Exception& e) {
        std::cerr << "Error at simulatorName: " << e.what() << std::endl;
        return;
    }
    
    //check if the simulatorVersion checks out with the already existing value
    if (simulatorVersion != persistentData["SimulatorVersion"].as<std::string>()){
        std::cerr << "Simulator version does not match the version in the persistent data file: " << simulatorVersion << " != " << persistentData["SimulatorVersion"].as<std::string>() << std::endl;
        return;
    }

    try{
        simulatorInfo.simulatorVersion = persistentData["SimulatorVersion"].as<std::string>();
    } catch (YAML::Exception& e) {
        std::cerr << "Error at SimulatorVersion: " << e.what() <<  std::endl;
    }
    
    //check to see if the build options are supported
    for (YAML::const_iterator it = persistentData["SupportedBuildOptions"].begin(); it != persistentData["SupportedBuildOptions"].end(); ++it){
        //Get the name of each individual supportedParameters and add it to the list of supportedParameters for the simulatorInfo.SupportedParameters
        try {
            simulatorInfo.supportedBuildOptions.emplace_back((*it)["BuildName"].as<std::string>());
        } catch (YAML::Exception& e) {
            std::cerr << "Error at SupportedBuildOptions: " << e.what() << std::endl;
            
        }
    }

    //Store the supported parameters for the simulator SMI from the persistentData
    for (YAML::const_iterator it = persistentData["SupportedParameters"].begin(); it != persistentData["SupportedParameters"].end(); ++it){
        //Get the name of each individual supportedParameters and add it to the list of supportedParameters for the simulatorInfo.SupportedParameters
        try {
            simulatorInfo.supportedParameters.emplace_back( (*it)["ParamName"].as<std::string>());
        } catch (YAML::Exception& e) {
            std::cerr << "Error at supportedParameters: " << e.what() << std::endl;
        }
    }

    //Store the supported metrics for the simulator SMI from the persistentData
    for (YAML::const_iterator it = persistentData["SupportedMetrics"].begin(); it != persistentData["SupportedMetrics"].end(); ++it){
        //Get the name of each individual supportedMetrics and add it to the list of supportedMetrics for the simulatorInfo.SupportedMetrics
        try {
            simulatorInfo.supportedMetrics.emplace_back( (*it)["MetricName"].as<std::string>());
        } catch (YAML::Exception& e){
            std::cerr << "Error at SupportedMetrics: " << e.what() << std::endl;
        }
    }

    /*Store the supported metrics for the simulator SMI from the persistentData*/
    this->simulatorInfo.simulatorName = SimulatorName;
    this->simulatorInfo.simulatorVersion = simulatorVersion;
    this->simulatorInfo.nativeOutputType = persistentData["SimulatorNativeOutput"].as<std::string>();
};

/**
 * @brief Modify the configuration of the simulator
 * @param configFileName 
 */
void NS3_mockup_interface::WriteToConfiguration(std::string configFileName){
    #ifdef DEBUG
        std::cout << "Writing to configuration is not supported for the NS3 simulator" << std::endl;
    #else
        std::cerr << "Writing to configuration is not supported for the NS3 simulator" << std::endl;
    #endif 
};

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
 * @brief load and crosscheck the metrics with the supported metrics from the simulator
 * @paragraph{The LoadMetrics function is used to crosscheck the supported metrics from the 
 * simulator with the metrics that are inputted in the benchmark yaml config file, 
 * and parsed to the individual scenarios where the variable called is metrics.}
 * 
 * @param metrics
 */
void NS3_mockup_interface::LoadMetrics(std::vector<Metrics>& metrics) {
    //Check if the metrics are supported by the simulator
    for(auto it = metrics.begin(); it != metrics.end(); ++it){
        //check if its supported and that the type inputed is matching the type supported by the simulator
        if(std::find(simulatorInfo.supportedMetrics.begin(), simulatorInfo.supportedMetrics.end(), (it->unit)) == simulatorInfo.supportedMetrics.end()){
            std::cerr << "Metric: " << (it->unit) << " is not supported by the simulator" << std::endl;
        }else{
            //if the metric is supported by the simulator, then add it to the metrics map
            NS3metrics.emplace_back(*it);
        }
    }
};

/**
 * @brief 
 * basic function which parses the parameters to an NS3 command line string for building the simulation
 * and the build options to an NS3 command line string for building the simulation
 * @param parameter
 * @return void
*/ 
void NS3_mockup_interface::ParseToNS3CommandLine(){

    std::string simulationFilePath = "";
    
    //Find the simulation file path
    for(auto it = NS3parameters.begin(); it != NS3parameters.end(); ++it){
        if((it->name) == "simulation-file-path" ){
            simulationFilePath = it->defaultParameter;
        }
    }

    //Get the file name without the file extension and path (remove after (.) and remove before (/)

    std::string tmpSimulatorFilePath = simulationFilePath.substr(simulationFilePath.find_last_of("/\\") + 1);
    tmpSimulatorFilePath = tmpSimulatorFilePath.find_last_of('.') != std::string::npos ? tmpSimulatorFilePath.substr(0, tmpSimulatorFilePath.find_last_of('.')) : tmpSimulatorFilePath;
    std::cout << "The simulation file path is: " << tmpSimulatorFilePath << std::endl;


    std::string BuildCMDstring = "python3 ./ns3 build " + tmpSimulatorFilePath + " "; //The simulation file path with the file extension
    std::string ParamsCMDstring = "python3 ./ns3 run " + tmpSimulatorFilePath + " "; //The simulation file path without the file extension 
    
    //Parse the build options to an NS3 command line string for building the simulation
    for(auto it = NS3buildOptions.begin(); it != NS3buildOptions.end(); ++it){
        BuildCMDstring += "--" + it->buildOption + "=" + it->buildOptionValue + " ";
    }

    //Parse the parameters to an NS3 command line string for building the simulation
    for(auto it = NS3parameters.begin(); it != NS3parameters.end(); ++it){
        if((it->name) != "simulation-file-path"){
            ParamsCMDstring += "--" + (it->name) + "=" + (it->defaultParameter) + " ";
        }else{
            continue;
        }
    }

    CL_Parameters = ParamsCMDstring;
    CL_BuildOptions = BuildCMDstring;

    return;
}


/**
 * @brief
 * Run the parsing function to parse the inputted parameters to an NS3 command line string for building the simulation
 * Set up a filestream which can capture the output from the simulation -out files stream and redirect the the listener
 * Run the simulation through command line the using the command line string 
 * @param parameters 
 * @return std::string 
 */
void NS3_mockup_interface::RunSimulation(){
    
    #ifdef DEBUG
        //this->simulatorInfo.simulatorName = "NS3";
        //this->simulatorInfo.simulatorVersion = "3.38";
        //this->simulatorInfo.nativeOutputType = "Float";
        //std::string configFile = "/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/test/NS3_Tests/NS3_run_tests/Tutorial_NS3_script.cc";
        //this->NS3parameters.emplace_back("simulation-file-path", configFile);
        //this->NS3metrics.emplace_back("Throughput", "Mbps");
        //this->NS3metrics.emplace_back("Delay", "ms");
        //this->NS3metrics.emplace_back("Jitter", "ms");
    #endif

    ParseToNS3CommandLine(); // Run the parsing function to parse the inputted parameters to an NS3 command line string for building the simulation

    //Get more precise time stamp for the output file "HourMinSec"
    auto currentTime = std::chrono::system_clock::now();
    std::time_t currentTimeInTimeT = std::chrono::system_clock::to_time_t(currentTime);
    std::tm* currentTimeInTM = std::localtime(&currentTimeInTimeT);

    std::string currentTimeInHourMinSec = 
        std::to_string(currentTimeInTM->tm_hour) + 
        std::to_string(currentTimeInTM->tm_min) + 
        std::to_string(currentTimeInTM->tm_sec);

    
    std::string fileOutput = simulatorInfo.simulatorName + "_" + currentTimeInHourMinSec + ".txt";

    std::cerr << "File output name: " << fileOutput << std::endl;

    CL_Parameters += "> " + ResultPath + "/" + fileOutput + " 2>&1";

    std::cout << "CL_Parameters: " << CL_Parameters << std::endl;
    std::cout << "CL_BuildOptions: " << CL_BuildOptions << std::endl;

    activeSimulatorListener->SimulationStart();

    //Change directory to the NS3-SMI directory
    std::string ns3_3_8 = "/ns-" + simulatorInfo.simulatorVersion;
    std::string changeDirectory = "cd "  + SMIPath + "/NS3-SMI" + ns3_3_8 + ns3_3_8;
    
    /*
    Todo:
    1. Get the path to the simulator and the simulation file path (done)
    2. Change directory to the simulator path (done)
    3. copy the simulation file to be run to the simulator path inside the src folder of the simulator into the scratch folder (done)
    4. build the simulation 
    5. run the simulation
    6. get the output from the simulation
    7. parse the output to the simulator output format
    8. delete the simulation file from the simulator path
    */

    std::string copySimulationCommand; 

    //checks to see if either a simulation-file-path or a simulation-file-path is given in the benchmark configuration file
    for(auto it = NS3parameters.begin(); it != NS3parameters.end(); ++it){
        if((it->name) == "simulation-file-path"){
            //copy the simulation file to the simulator path inside the src folder of the simulator into the scratch folder
            copySimulationCommand = "cp " + (it->defaultParameter) + " " + SMIPath + "/NS3-SMI" + ns3_3_8 + ns3_3_8 + "/scratch"; 
        }else if ((it->name) == "simulation-folder-path"){
            //copy the simulation folder to the simulator path inside the src folder of the simulator into the scratch folder
            copySimulationCommand = "cp -Rp " + (it->defaultParameter) + " " + SMIPath + "/NS3-SMI" + ns3_3_8 + ns3_3_8 + "/scratch";
        }else if(it == NS3parameters.end()){
            //if neither a simulation-file-path or a simulation-file-path is given in the benchmark configuration file
            std::cout << "No simulation file or folder defined in the benchmark configuration file" << std::endl;
            std::cout << "Terminating RunSimulation()" << std::endl;
            return;
        }else{
            continue;
        }
    }

    //build the command string
    std::string command = copySimulationCommand + " && " + changeDirectory + " && " + CL_BuildOptions + " && " + CL_Parameters;

     #ifdef DEBUG
        std::string partialCommand = copySimulationCommand + " && " + changeDirectory + " && " + CL_BuildOptions; 
        std::cout << "copySimulationCommand: " << copySimulationCommand << std::endl;
    #endif

    // Create a pipe to get a handle to the command output
    std::array<char, 128> buffer;

    //Run the command
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Failed to run NS3 command: " << command << std::endl;
        return;
    }

    //Read the output
    while (!feof(pipe)) {
        if (fgets(buffer.data(), 128, pipe) != nullptr) {
            std::cout << buffer.data();
        }
    }

    pclose(pipe);


    //Then we run the simulation
    //system(command.c_str());


    //#ifdef defined(__unix__) || defined(__unix) || defined(__linux__) || defined(linux)
    //    system(changeDirectory.c_str());
    //#endif
    
    //#ifdef _WIN64
        //Use wslapi.h to run the simulation
    //#endif


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
}

//void NS3_mockup_interface::GetRuntimeData(){};

