#include <iostream>
#include <core.Testbed.hpp>

#define DEBUG

int main(int argc, char** argv) {
    Testbed testbed;
    
    testbed.("test/NS3_Tests/NS3_input_tests/NS3_unsupported_Parameters.yaml");

    return 0;
}