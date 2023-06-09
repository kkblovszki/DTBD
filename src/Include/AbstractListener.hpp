#ifndef ABSTRACT_LISTENER_HPP
#define ABSTRACT_LISTENER_HPP

#include "core.Types.hpp"
#include <filesystem>
#include <optional>

/**
 * \page Listeners
 * @brief AbstractListener class
 * 
 * \section Listeners
 * 
 * Whether the individual listeners support updating in runtime depends on the individual Listener & SMI implementation respectively.
 * 
 * \subsection ListenersOverview
 * There are currently 3 core listeners implemented in the framework.
 * These being:
 * - TestListener
 * - ConsoleListener
 * - CSVListener
 * 
 * \subsection TestListener
 * The TestListener is a listener that is used for testing purposes.
 * 
 * \subsection ConsoleListener
 * 
 * The ConsoleListener is the default listener that is used by the framework and outputs the simulation results to the console.
 * 
 * \subsection CSVListener
 * 
 * The CSVListener is a listener that outputs the simulation results to a CSV file.
 *  
 */
class Listener {
public:
    Listener(){};
    ~Listener(){};
    
    Measure measurements;

    /**
     * @brief Get the Measurements object
     * @details This function returns the measurements of the simulation in the form of a read-only Measure object.
     * @note Here's an example usage:
     * @code{.cpp}
     * // Retrieve multiple measurements using GetMeasurements()
     * std::vector<Measure> measurementsCollection = GetMeasurements();
     *
     * // Iterate over the measurements
     * for (const auto& measurement : measurementsCollection) {
     *     // Access the individual measurement properties
     *     std::string label = measurement.label;
     *     std::map<Metrics, std::vector<std::string>> readings = measurement.readings;
     *
     *     // Process or utilize the measurement as needed
     *     // ...
     * }
     * @endcode
     * @return const Measure& 
     */
    //const Measure& GetMeasurements() const {
    //    //lot of const here haha :D, but it is needed to make sure that the user does not change the measurements 
    //    if (measurements.isMeasureEmpty()){
    //        static Measure emptyMeasure;
    //        return emptyMeasure; 
    //    }
    //    else{
    //        return measurements;
    //    }
    //}

    void SimulationStart(){
        OnSimulationStart();
    }

    void SimulationStart(std::vector<Metrics> metrics){
        OnSimulationStart(metrics);
    }

    void SimulationEnd(){
        OnSimulationEnd();
    }

    void SimulationEnd(std::filesystem::path filepath){
        OnSimulationEnd(filepath);
    }

    void SimulationEnd(std::string value){
        OnSimulationEnd(value);
    }

    void SimulationUpdate(std::string value){
        OnSimulationUpdate(value);
    }

    void SimulationUpdate(std::vector<std::string> values){
        OnSimulationUpdate(values);
    }

    void SimulationUpdate(Metrics metric, std::vector<std::string> values){
        OnSimulationUpdate(metric, values);
    }

    void SimulationUpdate(Metrics metric, std::string value){
        OnSimulationUpdate(metric, value);
    }

    void SimulationResult(){
        OnSimulationResult();
    }

private:    
    virtual void OnSimulationStart(){};
    virtual void OnSimulationResult(){};
    virtual void OnSimulationEnd(){};
    
    virtual void OnSimulationStart(std::vector<Metrics> metrics){};
    
    virtual void OnSimulationEnd(std::filesystem::path filepath){};

    virtual void OnSimulationEnd(std::string value){};

    virtual void OnSimulationUpdate(std::string value){};
    virtual void OnSimulationUpdate(std::vector<std::string> values){};
    virtual void OnSimulationUpdate(Metrics, std::vector<std::string>){};
    virtual void OnSimulationUpdate(Metrics, std::string){};
};


#endif