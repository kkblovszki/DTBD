#include "Include/ListenerCreator.hpp"

/**
 * @brief This function is responsible for creating the listener instances
 * @param listenerType 
 * @return std::unique_ptr<Listener> 
 */
std::unique_ptr<Listener> ListenerCreator::CreateListener(const std::string& listenerType){

    #ifdef DEBUG
    std::cout << "Creating listener of type: " << listenerType << std::endl;
    #endif

    std::string ListenerType = stringForceUpperCase(listenerType);

    #ifdef DEBUG
    std::cout << "UpperCase name: " << ListenerType << std::endl;
    #endif

    switch (stringToListenerType().at(ListenerType)) {
        case ListenerType::TestListener:
            return std::make_unique<Core::Listeners::TestListener>();
            break;
        case ListenerType::ConsoleListener:
            return std::make_unique<Core::Listeners::ConsoleListener>();
            break;
        case ListenerType::CSVListener:
            return std::make_unique<Core::Listeners::CSVListener>();
            break;
        
        default:
            return nullptr;
            break;
    }
}