#include "core.Types.hpp"
#include "Listener.hpp"

class ListenerCreator {
public:
    virtual ~ListenerCreator() {}

    static const std::unique_ptr<Listener> createListener(const std::string& listenerType);
};