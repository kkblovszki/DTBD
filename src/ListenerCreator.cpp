#include "Include/ListenerCreator.hpp"

std::unique_ptr<Listener> ListenerCreator::CreateListener(const std::string& listenerType){
    if (listenerType == "DefaultListener") {
        return std::make_unique<Core::Listeners::TestListener>(); // std::make_unique<Listeners::Default::TestListener>();
    }
    else {
        return nullptr;
    }
}