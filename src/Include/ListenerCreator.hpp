#ifndef LISTENER_CREATOR_HPP
#define LISTENER_CREATOR_HPP

#include "core.Types.hpp"
#include "AbstractListener.hpp"
#include "Listener.hpp"


/***
 * \class ListenerCreator
 * \brief This class is responsible for creating the listener instances
 * \details This class is responsible for creating the listener instances. It contains a map of strings to listener types, which is used to create the listener instances.
 * \author Mikkel Silkeborg & Asbjørn Nielsen
 * \date 2023-03-05
*/
class ListenerCreator {
private:
    
    enum class ListenerType {
        TestListener,
        DefaultListener,
        CustomListener
    };

    static const std::string stringForceUpperCase(std::string inputString){
        std::transform(inputString.begin(), inputString.end(), inputString.begin(), ::toupper);
        return inputString;
    }
    
    static const std::map<std::string, ListenerType>& stringToListenerType(){
        static const std::map<std::string, ListenerType> stringToListenerType = {
            {"TESTLISTENER", ListenerType::CustomListener},
            {"DEFAULTLISTENER", ListenerType::DefaultListener},
            {"CUSTOMLISTENER", ListenerType::CustomListener}
        };
        return stringToListenerType;
    }

public:
    ListenerCreator(){}
    ~ListenerCreator(){}

    static std::unique_ptr<Listener> CreateListener(const std::string& listenerType);
};

#endif