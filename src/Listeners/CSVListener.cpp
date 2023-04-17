#include "../Include/Listener.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

using namespace Core::Listeners;


CSVListener::CSVListener(){}

CSVListener::~CSVListener(){}

void CSVListener::OnSimulationStart(std::vector<Metrics> metrics){
    //open the csv file
    std::cout << "Simulation start" << std::endl;
}

void CSVListener::OnSimulationEnd(){
    //close the csv file
    std::cout << "Simulation end" << std::endl;
}

void CSVListener::OnSimulationUpdate(std::string value){   
    //write the value to the csv file
    std::cout << value << std::endl;
}

void CSVListener::OnSimulationResult(){
    std::cout << "Simulation result" << std::endl;
}

    


