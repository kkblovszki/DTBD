#include "include/SimulatorCreator.hpp"
#include <dlfcn.h>

//i want to add code documentation of the SimulatorCreator::createsimulator function to doxygen. how can i do it?


const std::map<std::string, SimulatorCreator::SimulatorType>& SimulatorCreator::stringToSimType() {
    static const std::map<std::string, SimulatorType> simMap = {
        {"EVOCRAFT", SimulatorType::EVOCRAFT},
        {"ALCHEMIST", SimulatorType::ALCHEMIST},
        {"NS3", SimulatorType::NS3}
    };
        
    return simMap;
}


/** 
 * @brief function that creates a simulator object based on the name of the simulator
 * @param simulatorName The name of the simulator
 * @return a unique pointer to the simulator object
 * @throws invalid_argument if the simulatorName is not supported
 * @details This function creates a simulator object based on the name of the simulator. 
 * It uses the dlopen function to load the shared library of the simulator and then uses the dlsym function to get the address of the constructor function of the simulator.
 * Then it calls the constructor function to create an instance of the simulator and returns a unique pointer to the simulator object.
 * By using a individual shared library for each simulator, the simulator can be easily replaced by another simulator without having to recompile the whole project,
 * while ensuring that each simulator instance have its own library handle.
 */
std::unique_ptr<SimulatorMockUpInterface> SimulatorCreator::CreateSimulator(const std::string& simulatorName){
    // Load the shared library of the specific simulator
    std::string libName = "./bin/shared_libs/lib" + simulatorName + "Simulator.so";
    void* libraryHandle = dlopen(libName.c_str(), RTLD_LAZY);
    if (!libraryHandle) {
        std::cerr << "Error loading dynamic library: " << dlerror() << "\n";
        return nullptr;
    }

    // Get the address of the constructor function for the specific simulator
    std::string constructorName = "_ZN" + simulatorName.length() + simulatorName + "SimulatorC1Ev";
    void* constructor = dlsym(libraryHandle, constructorName.c_str());
    if (!constructor) {
        std::cerr << "Error getting constructor address: " << dlerror() << "\n";
        dlclose(libraryHandle);
        return nullptr;
    }

     // Cast the constructor function pointer to the appropriate type
    using CreateFunc = SimulatorMockUpInterface* (*)();
    CreateFunc createFunc = reinterpret_cast<CreateFunc>(constructor);
    // Call the constructor function to create an instance of the specific simulator
    auto simulator = createFunc();
    simulator->setLibraryHandle(libraryHandle);

    return std::unique_ptr<SimulatorMockUpInterface>(simulator);

    switch (stringToSimType().at(simulatorName)) {
        case SimulatorType::EVOCRAFT:
            std::cout << "Creating Evocraft simulator" << std::endl;
            return std::make_unique<EvocraftSimulator>(simulator);
            break;
        case SimulatorType::ALCHEMIST:
            std::cout << "Creating Alchemist simulator" << std::endl;
            break;
        case SimulatorType::NS3:
            std::cout << "Creating NS3 simulator" << std::endl;
            break;
        default:
            std::cerr << "Error: Simulator type not supported" << std::endl;
            dlclose(libraryHandle);
            return nullptr;
    }

   
    
};

