#include "core.Types.hpp"
#include "AbstractListener.hpp"
#include "Listener.hpp"

class ListenerCreator {
public:
    ListenerCreator(){}
    ~ListenerCreator(){}

    static std::unique_ptr<Listener> CreateListener(const std::string& listenerType);
};