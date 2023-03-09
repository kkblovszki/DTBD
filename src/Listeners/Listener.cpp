#include "./include/Listener.hpp"
#include <iostream>

namespace Listeners {
    namespace Default {

        class TestListener : public Listener {
        private:
            /* data */
        public:
            TestListener();
            ~TestListener();

            void OnSimulationStart(std::vector<Metrics> metrics) override {
                std::cout << "Simulation started" << std::endl;
            };

            void OnSimulationEnd() override {
                std::cout << "Simulation ended" << std::endl;
            };

            void OnSimulationUpdate() override {
                std::cout << "Simulation updated" << std::endl;
            };

            void OnSimulationResult() override {
                std::cout << "Simulation result" << std::endl;
            };
        };

        class DefaultSimulatorListener : public Listener {
        private:
            /* data */
        public:
            DefaultSimulatorListener(/* args */);
            ~DefaultSimulatorListener();

            void OnSimulationStart(std::vector<Metrics> metrics) override {
                std::cout << "Simulation started" << std::endl;
            };

            void OnSimulationEnd() override {
                std::cout << "Simulation ended" << std::endl;
            };

            void OnSimulationUpdate() override {
                std::cout << "Simulation updated" << std::endl;
            };

            void OnSimulationResult() override {
                std::cout << "Simulation result" << std::endl;
            };
        };
    
    
    
    }
}

