# Digital Benchmark and Testbed framework for self-adaptive and self-organising systems

## Bachelor Thesis

This project implements a unified framework for the use of, but not limited to, self-adaptive and self-organising systems.
It was developed as part of our bachelor thesis titled "Digital Bestbed and Benchmark Development For Self-Adaptive And Self-Organising Systems"

**Authors:** Asbjørn Verner Nielsen & Mikkel Rohde Silkeborg 

**Year:** 2023

**University:** Aarhus University  

**Department:** Institute for Electro- and Computertechnology

**Thesis Supervisor:**  Lukas Esterle


### Todo

###### To reach MVP:
- Ensure that BuildOptions are correctly parsed to the simulator
- Move the actual simulators into the build folder with its persistent data 
- Clean up the code
- Write a debug simulator mock-up interface that can be used to test the framework. 
- Test Parser, and make sure that it works correctly, and parses into the correct data structures.
- Test the framework with the NS3 simulator mock-up interface
- Write a CommandLine listener which outputs the runtime data to the CommandLine
- Write many more tests to test edge cases both in parser and framework core.


###### Further development after MVP:
- Rewrite the parser to use recursion for nested sequences and maps.
- Add more error catching.
- Modify the simulators SMI into a custom binary filetype.
- Maybe use Getters and setters to hide the data variables in the core framework?
- Add support for parallel execution
- Add Valgrind support (debugging memory leaks, etc.)
- Add support for more simulators
- Add support for Windows and Mac OS X
- More Proper implementation and consistent loading for the simulators which doesn't use the current hacky solution of a cmake macro
- LoadConfiguration could maybe get abstracted into the core framework, and the simulators could just call it when they need to load a configuration file with the appropriate arguments.

## Introduction
This framework is a software package that does something cool. It's written in C++ and uses the
NS-3 network simulation framework to simulate network traffic and analyze network performance.

## Installation 

To be added

## Usage
To use the framework, you need to have the individual simulator mock-up interfaces for each individual simulator and the source code, to build the framework.
You can then build the framework using the included build system, either cmake (maybe ninja in the future), and run the included examples to see how it works.
To use the framework, a simulation configuration for the benchmark is needs to be created. This configuration file is a YAML file that contains the configuration for the benchmark.  
in the case of multiple benchmarks. multiple configuration files are needs to be created. 

#### Example

```YAML
Profile-name: NS3_single_simulation
Benchmark:
- Simulator: NS3
   Scenario: 
   name: NS3 Example
   description: An example problem in NS3
   simulator: NS3
   optional: null
   required:
     topology-file-path: network.cpp
     traffic-file-path: traffic.cpp
     - BuildOptions:
       examples: enable
       tests: enable
       python: disable
       gs1: enable
       ns3-mobility: enable
       system-libraries: enable
       precompiled-header: enable
       
       - openflow:
         enable: enable
         openflow-version: 1.3
         openflow-protocol: OpenFlowSwitch13
         openflow-helper: OpenFlowHelper
         openflow-controller: RemoteController
       performance: trace
       - brite:
         enable: enable
         brite-version: 1.3
         brite-protocol: BriteTopologyHelper
         brite-helper: BriteHelper
         brite-controller: BriteControllerHelper
       prefix: /usr/local

      - Parameters:
        protocol: TCP
        tcp-variant: NewReno
        routing-protocol: OSPF

 - Simulator: OMNET++
```
Here's an example of how to initialise the framework in your own code:

```C++
#include <core.Testbed.hpp>
int main ()
{
    Testbed Testbed;
    return 0;
}
```

To compile the code in debug mode the following flag is used when running the make file  * make CXXFLAGS="-DDEBUG" * 
To compile the tests the make flag "COMPILE-TESTS" must be set equal to "true"
To run tests CTests can be used, by using the following command: ctest -VV 'testname', example could be: ctest -VV -R CreateBenchmark

As for the flags -VV is a verbose flag that will print out the output of the tests and -R can be used to run a specific test.

### Currently supported features
- Currently only Linux is supported as a build platform (Windows and Mac OS X support is planned)
- Currently only sequential execution is supported (parallel execution is planned)
- Multiple scenarios
- Multiple Benchmarks
- NS3 simulator mock-up interface(SMIs)
- Dynamic loading of SMI
- Dynamic Creation or removal of Benchmark and scenarios
- Basic parser for the Benchmark configuration file



## NS-3 Simulator
how does it work in-code:
When creating a new simulator, the following steps need to be taken:
- Run constructor:
     
- load the APIFunctionPassThrough from the NS3_config.yaml file
- Return a NS3_mockup_interface object from the createSimulator function

When the LoadConfiguration function is called, the following steps need to be taken:
- load the persistent data from the NS3_config.yaml file
         - Get the supported parameters

- Crosscheck the supported parameters from the simulator with the inputted parameters
- If the parameters are supported, then pass them to the simulator else throw an error saying that the specific parameter(s) are not supported
- It then creates a list of the supported metrics and parameters from the simulator

When the LoadMetrics function is called, the following steps need to be taken:
- Convert the standardized metrics to the simulator specific metrics types 

When the LoadParameters function is called, the following steps need to be taken:
- Get the inputted parameters from the benchmark yaml file
- Convert the standardized parameters to the simulator specific parameters types i.e. BuildOptions Type

When the ParseToNS3CommandLine function is called, the following steps need to be taken:
- Parse the inputted parameters to an NS3 command line string for building the simulation  
 
When RunSimulation is called, the following steps need to be taken:
- Run the parsing function to parse the inputted parameters to an NS3 command line string for building the simulation
- Set up a filestream to read the output from the simulation
- Run the simulation
- Read the output from the simulation


##### Links
Links to the simulators currently supported can be found here:
For more information about NS-3, see the <a href="http://www.nsnam.org">NS-3 website</a>.