#include "Include/ListenerCreator.hpp"

std::unique_ptr<Listener> ListenerCreator::createListener(const std::string& listenerType) {
    if (listenerType == "DefaultListener") {
        return nullptr; // std::make_unique<Listeners::Default::TestListener>();
    }
    else {
        return nullptr;
    }
}