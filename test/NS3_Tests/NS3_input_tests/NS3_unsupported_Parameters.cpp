#include <iostream>
#include <../core.Testbed.hpp>

#define DEBUG

int main(int argc, char** argv) {
    Testbed testbed;
    
    testbed.LoadSimulationConfig("test/NS3_Tests/NS3_input_tests/NS3_unsupported_Parameters.yaml");
    testbed.CreateBenchmark("NS3_unsupported_config_params_test");
    testbed.benchmarks["NS3_unsupported_config_params_test"].CreateScenario("NS3_unsupported_config_params_test");
    

    return 0;
}
