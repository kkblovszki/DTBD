#include "Include/ListenerCreator.hpp"

/**
 * @brief This function is responsible for creating the listener instances
 * @param listenerType 
 * @return std::unique_ptr<Listener> 
 */
std::unique_ptr<Listener> ListenerCreator::CreateListener(const std::string& listenerType){
    std::cout << "Creating listener of type: " << listenerType << std::endl;

    std::string ListenerType = stringForceUpperCase(listenerType);
    
    switch (stringToListenerType().at(ListenerType)) {
        case ListenerType::DefaultListener:
            return std::make_unique<Core::Listeners::DefaultListener>();
            break;
        case ListenerType::TestListener:
            std::cout << "Creating test listener" << std::endl;
            return std::make_unique<Core::Listeners::TestListener>();
            break;
        default:
            return nullptr;
            break;
    }
}