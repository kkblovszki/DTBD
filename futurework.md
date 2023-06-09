
### future-iterations Future Iterations
This page contains code snippets that are intended for use in future
iterations of the software project. This code should not be part of the
public API and is subject to change.

- Simulator Mockup Interface (SMI)

#### framework Framework

##### framework-multi-process-parallel-exec Multi-Processing/Parallel execution Support
Add support for multi-processing and parallel execution to the framework.
This would allow the user to run multiple simulations at the same time while using the most of the available resources.
Seems kind of obvious that its purpose is to cut down the time it takes when running multiple simulators. 

##### framework-multi-listener Multi-Listener Support

Add support for multiple listeners to the framework.
This would allow multiple applications to receive the same
data from the framework or any other SMI. See @ref ns3-smi-multi-listener for more information regarding the SMI part of this feature.
todo: add code snippet
The code snippet below is an idea of how the SetListener function could be implemented to abstract it away from the SMI's.

```C++
//universal function to set the listener idea
/**
 * @brief Set the Listener object
 * Using this function which takes two parameters @param uniqueListener and @param simulatorUniqueListener
 * the simulator can set the listener that is used by the simulator, the unique listener is the 
 * listener that is created in the constructor of a scenario while the simulatorUniqueListener 
 * is the listener that is used by the simulator.
 * @param uniqueListener The created listener
 * @param simulatorUniqueListener The listener that is used by the simulator
 *
*/
virtual void SetListener(std::unique_ptr<Listener> uniqueListener, std::unique_ptr<Listener> simulatorUniqueListener) override {
    simulatorUniqueListener = std::move(uniqueListener); uniqueListener.reset(); 
}
```

##### framework-remote-execution Remote Execution
Add support for remote execution to the framework. 
This would allow the user to execute the framework on a remote machine.
This would be useful for both testing purposes, and for running the framework on a machine with more resources.

##### framework-logging Logging
Add logging to the framework.
This would allow the user to see what the framework is doing after each execution. 
This would be useful for debugging purposes.

##### framework-simulators-DSL Domain Specific Language (DSL) for Simulators

By creating a tokenizer and specific grammar, we can create a "unified" DSL for the simulators.
This is what the @ref SimulatorMockUpInterface::APIFunctionPassThrough is intended for.

#### ns3-smi NS3 SMI

##### ns3-smi-multi-listener Multi-Listener Support
Add support for multiple listeners to the NS3 SMI.
This would allow multiple applications to receive the same
data from the NS3 SMI or any other SMI.
Here's an example of some code that might be intended for future use:

- Benchmark.cpp
- CreateScenario
- 60~65
```C++
for(auto it = scenariosDescriptors.begin(); it != scenariosDescriptors.end(); ++it){
      if(it->first == scenarioName){
          if(it->second.listener != ""){
              listener = std::make_shared<Listener>(it->second.listener);
          }
      }
  }
```

##### ns3-smi-runtime-results Runtime Results
 
This is generally specific for any simulators which uses a CLI to run simulations.
NS-3 is one of these simulators, and it would be useful to be able to get the results of a simulation while it is running.
Ofcourse its possible to get the results output. However this is done outside of the framework and requires the user to know the exact location of the output file.
Even if the output is predefined, it would be nice to have it connected to the framework using a listener.
This would allow the user to get the results of a simulation while it is running through the framework.
Which will enable the user to do something with the results while the simulation is running as in parsing the results to CSV or JSON file.
This would also allow the user to get the results of a simulation without having to know the exact location of the output file.
Here's an example of some code that might be intended for future use:
This code snippet uses the filestream created in the @ref NS3_mockup::RunSimulation function.
to read the output file line by line and send it to the listener using a thread.

- file: NS3_SMI.hpp
- func: UpdateListener
- private
```C++
void UpdateListener(std::ifstream& outputFileStream){
      std::string line;
      if(outputFileStream.is_open()){
          while(getline(outputFileStream, line)){
              activeSimulatorListener->OnSimulationUpdate(line);
              std::this_thread::sleep_for(std::chrono::nanoseconds(100));
          }
          outputFileStream.close();
      }
  }
``` 
  
- file: NS3_SMI.cpp
- func: RunSimulation
```C++
 namespace fs = std::filesystem;
 fs::path tempPath = fs::temp_directory_path()/"output.txt";
  
 std::ofstream outputFile(tempPath);
  
 //redirect the output to the file
 std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
 std::cout.rdbuf(outputFile.rdbuf());
 
 //Run the simulation through command line the using the command line string
 activeSimulatorListener->OnSimulationStart(NS3metrics);
 //First we build the simulation
 system(CL_BuildOptions.c_str());
 std::thread ThreadUpdate(UpdateListener);
  
 //Wait for thread to finish
 ThreadUpdate.join();
 activeSimulatorListener->OnSimulationEnd();
 //Cleanup
 std::cout.rdbuf(oldCoutStreamBuf); //Reset the cout stream buffer
 fs::remove(tempPath); //remove the file
```

This code should not be used in the current version of the software,
but may be useful in future iterations.
