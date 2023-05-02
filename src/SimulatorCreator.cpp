#include "include/SimulatorCreator.hpp"
#include <dlfcn.h>


/*!
    @brief function that converts a string to a SimulatorType enum value for the simulator creator function
    @details converts a string to a SimulatorType enum value for the simulator creator function
    @return const std::map<std::string, SimulatorCreator::SimulatorType>&
 */
const std::map<std::string, SimulatorCreator::SimulatorType>& SimulatorCreator::stringToSimType() {
    static const std::map<std::string, SimulatorType> simMap = {
        {"EVOCRAFT", SimulatorType::EVOCRAFT},
        {"ALCHEMIST", SimulatorType::ALCHEMIST},
        {"NS3", SimulatorType::NS3}
    };
    return simMap;
}

/*! 
    @brief function that creates a simulator object based on the name of the simulator
    @param simulatorName The name of the simulator
    @return a unique pointer to the simulator object
    @throws invalid_argument if the simulatorName is not supported
    @details This function creates a simulator object based on the name of the simulator. 
    It uses the dlopen function to load the shared library of the simulator and then uses the dlsym function to get the address of the constructor function of the simulator.
    Then it calls the constructor function to create an instance of the simulator and returns a unique pointer to the simulator object.
    By using a individual shared library for each simulator, the simulator can be easily replaced by another simulator without having to recompile the whole project,
    while ensuring that each simulator instance have its own library handle.
 */
std::unique_ptr<SimulatorMockUpInterface> SimulatorCreator::CreateSimulator(const std::string& simulatorName){

    /*!
    \note - Fun fact: the simulator object is created in the shared library, but the library handle is in the main program 
    */

    // Check if the simulator name is supported
    auto upperCaseSimulatorName = stringForceUpperCase(simulatorName);

    if (stringToSimType().find(upperCaseSimulatorName) == stringToSimType().end()) {
        throw std::invalid_argument("Simulator name not supported");
    }

    //find the dynamic/shared libraries
    std::string LibraryPath = __FILE__;
    std::string LibraryDir = LibraryPath.substr(0, LibraryPath.find_last_of("/\\")) + "/../build/bin/shared_libs/";

    // Load the shared library of the specific simulator
    std::string libName = LibraryDir + "lib" + upperCaseSimulatorName + "Simulator.so";
    std::shared_ptr<void> libraryHandle(dlopen(libName.c_str(), RTLD_LAZY), dlclose);
    if (!libraryHandle) {
        std::cerr << "Error loading dynamic library: " << dlerror() << "\n";
        return nullptr;
    }

    // Get the name of the class for the specific simulator
    std::string simulatorClassName = upperCaseSimulatorName + "_mockup_interface";

    // Get the address of the constructor function for the specific simulator
    std::string constructorFnName = "_ZN" + std::to_string(simulatorClassName.length()) + simulatorClassName + "15createSimulatorEv";

    using CreateSim = SimulatorMockUpInterface* (*)(); // define a function pointer type for the constructor function

    auto LibSymbols = dlsym(libraryHandle.get(), constructorFnName.c_str()); // get the address of the constructor function
    if (!LibSymbols){
        std::cerr << "Error getting constructor address: " << dlerror() << "\n";
        return nullptr;
    }

    CreateSim SimConstructor = std::bit_cast<CreateSim>(LibSymbols);

    std::unique_ptr<SimulatorMockUpInterface> simulator(SimConstructor()); // call the constructor function to create an instance of the simulator
    
    /*!
    \note 
        Fun fact: using the std::move function on a shared_ptr, is much faster than copying the shared_ptr. 
        Since we basically steal the atomic reference counter from the shared_ptr and give it to another smart pointer. (yoink)
        This is because "stealing" the reference count isn't atomic.
    */
    simulator->setLibraryHandle( std::move(libraryHandle) ); // set the library handle for the simulator object

    return simulator;    
};

