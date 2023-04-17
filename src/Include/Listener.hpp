#ifndef LISTENER_HPP
#define LISTENER_HPP

#include "AbstractListener.hpp"

/**
 * \page Listeners
 * 
 * \section Listeners
 * 
 * Whether the individual listeners support updating in runtime depends on the individual Listener & SMI implementation respectively.
 * 
 * \subsection ListenersOverview
 * There are currently 3 core listeners implemented in the framework. 
 * These being:
 * - TestListener
 * - DefaultListener
 * - CSVListener
 * 
 * \subsection TestListener
 * The TestListener is a listener that is used for testing purposes.
 * 
 * \subsection DefaultListener
 * The DefaultListener is the default listener that is used by the framework and outputs the simulation results to the console.
 * 
 * \subsection CSVListener
 * The CSVListener is a listener that outputs the simulation results to a CSV file.
 * 
 */
namespace Core {
    namespace Listeners {

        class TestListener : public Listener {
        public:
            TestListener();
            ~TestListener();

            void OnSimulationStart() override;
            void OnSimulationEnd() override;
            void OnSimulationResult() override;
            
            void OnSimulationUpdate(std::string value) override;
        };

        class ConsoleListener : public Listener {
        public:
            ConsoleListener();
            ~ConsoleListener();

            void OnSimulationStart() override;
            void OnSimulationEnd() override;
            void OnSimulationResult() override;
            void OnSimulationUpdate(std::string value) override;
        };


        class CSVListener : public Listener {
        public:
            CSVListener();
            ~CSVListener();

            void OnSimulationStart(std::vector<Metrics> metrics) override;
            void OnSimulationEnd() override;
            void OnSimulationUpdate(std::string value) override;
            void OnSimulationResult() override;
        };

    };
};


#endif