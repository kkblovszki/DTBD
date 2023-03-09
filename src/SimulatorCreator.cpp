#include "include/SimulatorCreator.hpp"
#include <dlfcn.h>

SimulatorCreator::SimulatorCreator(/* args */){}
SimulatorCreator::~SimulatorCreator(){}

//i want to add code documentation of the SimulatorCreator::createsimulator function to doxygen. how can i do it?

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
    auto stringType = stringToSimType().find(simulatorName);
    if (stringType == stringToSimType().end()) {
        throw std::invalid_argument("Unsupported Simulator");
    }
    
    std::string libName = "./lib" + simulatorName + "Simulator.so";
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
    SimulatorMockUpInterface* simulator = createFunc();

    simulator->setLibraryHandle(libraryHandle);

    return std::make_unique<SimulatorMockUpInterface>(simulator);
    
};

