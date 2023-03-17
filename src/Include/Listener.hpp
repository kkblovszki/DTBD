#ifndef LISTENER_HPP
#define LISTENER_HPP

#include "AbstractListener.hpp"


/**
 * @brief This class is responsible for creating the listener instances
 */
namespace Core {
    namespace Listeners {

        class TestListener : public Listener {
        public:
            TestListener();
            ~TestListener();

            void OnSimulationStart(std::vector<Metrics> metrics) override;
            void OnSimulationEnd() override;
            void OnSimulationUpdate() override;
            void OnSimulationResult() override;
        };

        class DefaultListener : public Listener {
        public:
            DefaultListener();
            ~DefaultListener();

            void OnSimulationStart(std::vector<Metrics> metrics) override;
            void OnSimulationEnd() override;
            void OnSimulationUpdate() override;
            void OnSimulationResult() override;
        };
    };
};


#endif