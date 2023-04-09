#include "../Include/Listener.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>


using namespace Core::Listeners;


CSVListener::CSVListener(){
    //create a new csv file with the current date and time as the name of the file 

    //write the header of the csv file
}

CSVListener::~CSVListener(){
}

void CSVListener::OnSimulationStart(std::vector<Metrics> metrics){
}

void CSVListener::OnSimulationEnd(){}

void CSVListener::OnSimulationUpdate(std::string value){   
    //write the value to the csv file
}

void CSVListener::OnSimulationResult(){
}

// Path: src/Listeners/CSVListener.cpp

    


