#ifndef ABSTRACT_LISTENER_HPP
#define ABSTRACT_LISTENER_HPP

#include "core.Types.hpp"
#include <filesystem>

class Listener {
public:
    Listener(){};
    ~Listener(){};
    
    Measure measurements;

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