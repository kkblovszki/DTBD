#include "Include/Parser.hpp"


/**
 * @brief 
 * @param scenarioNode 
 * @param scenario 
 */

/*Its way too nested and complicated, we should split it up 
into smaller functions and use recursion (it's a mess) :'(*/
void Parser::parseScenario(const YAML::Node& scenarioNode, ScenarioDescriptor& scenario) {
    scenario.name = scenarioNode["Name"].as<std::string>();
    scenario.description = scenarioNode["Description"].as<std::string>();
            
    //check if the scenario node is the optional node
    //Only supports single variables, no maps or sequences!
    if(scenarioNode["Optional"]) {
        const auto& optionalNode = scenarioNode["Optional"];
        for (auto it = optionalNode.begin(); it != optionalNode.end(); ++it) {
            if(it->first.as<std::string>() == "Optional"){
                continue;
            }else{
                scenario.optional[it->first.as<std::string>()] = it->second.as<std::string>();
            }
        }
    }

    //check if the scenario node is the required node
    if(scenarioNode["Required"]) {
    const auto& requiredNodes = scenarioNode["Required"];
    for(auto& requiredNode : requiredNodes) {
        if(requiredNode.IsMap()) {
            //check if the required node is the parameter node
            if(requiredNode["Parameters"]) { 
                const auto& parametersNode = requiredNode;
                for(auto it = parametersNode.begin(); it != parametersNode.end(); ++it) {
                    #ifdef DEBUG
                    std::cout << "Key: " << it->first.as<std::string>() << " Value: " << it->second.as<std::string>() << std::endl;
                    #endif
                    
                    if(it->first.as<std::string>() == "Parameters"){ //we dont want the parameters value we use as an identifier
                        continue;
                    }
                    scenario.required[it->first.as<std::string>()] = it->second.as<std::string>();//insert into required
                    Parameter tmpParam = {it->first.as<std::string>(), it->second.as<std::string>()}; //Create temp variable to emplace back
                    scenario.parameters.emplace_back(tmpParam);  //Insert into parameters
                }
            }

            //check if the required node is the BuildOptions node
            else if(requiredNode["BuildOptions"])  {
                const auto& buildOptionsNode = requiredNode;
                for (auto it = buildOptionsNode.begin(); it != buildOptionsNode.end(); ++it) {
                    if(it->first.as<std::string>() == "BuildOptions"){
                        continue;
                    }else{
                        BuildOptions buildOptions;
                        buildOptions.buildOption = it->first.as<std::string>();
                        buildOptions.buildOptionValue = it->second.as<std::string>();
                        scenario.required[it->first.as<std::string>()] = it->second.as<std::string>(); //insert into required
                        scenario.buildOptions.emplace_back(buildOptions); //Insert into buildOptions
                    }
                }
            }else   { 
                //If its neither a parameter or build options, just insert it into the required map for later processing
                for(auto it = requiredNode.begin(); it != requiredNode.end(); it++) {
                    if(it->second.IsScalar()) {
                        #ifdef DEBUG
                        std::cout << "IsScalar: True; Key: " << it->first.as<std::string>() << "Value: " << it->second.as<std::string>() << std::endl;
                        #endif
                        scenario.required[it->first.as<std::string>()] = it->second.as<std::string>();
                    }else {
                        const auto& mapNode = it->second;
                            for(auto it2 = mapNode.begin(); it2 != mapNode.end(); ++it2) {
                                #ifdef DEBUG
                                std::cout << "IsScalar: False; Key: " << it2->first.as<std::string>() << "Value: " << it2->second.as<std::string>() << std::endl;
                                #endif
                                scenario.required[it->first.as<std::string>() + "." + it2->first.as<std::string>()] = it2->second.as<std::string>();
                            }
                        }
                    }
                }
            }
        }
    }
}


/**
 * @brief 
 * 
 * @param simulationStrategyNode 
 * @param simulationStrategy 
 */
void Parser::parseSimulationStrategy(const YAML::Node& simulationStrategyNode, SimulationStrategy& simulationStrategy) {
    simulationStrategy.multithread = simulationStrategyNode["Multithread"].as<bool>();
    simulationStrategy.threadNr = simulationStrategyNode["Thread_nr"].as<int>();
    const auto& executionOrderNode = simulationStrategyNode["ExecutionOrder"];
    for (const auto& it : executionOrderNode) {
        simulationStrategy.executionOrder[it.first.as<int>()] = it.second.as<std::string>();
    }
}

/**
 * @brief 
 * This function takes an entire benchmarks and parses it into cpp objects, to standardise the data through the framework.
 * This is done to ensure simple rules in the YAML configuration file is followed.
 * 
 * If we find the simulation strategy we parse it into a SimulationStrategy object.
 * If we find the simulator we parse each scenario in this simulator node into a ScenarioType object.
 * 
 * @param benchmarkNode 
 * @param ScenarioDescriptors
 * @param simulationStrategy
 */
void Parser::parseBenchmark(YAML::Node& benchmarkNode, std::map<std::string, ScenarioDescriptor>& ScenarioDescriptors, SimulationStrategy& simulationStrategy) {
    benchmarkNode = benchmarkNode["Benchmark"];
    if (benchmarkNode.IsSequence()) {
        for (const auto& node : benchmarkNode) {
            if (node["SimulationStrategy"]) {
                Parser::parseSimulationStrategy(node, simulationStrategy);
            }
            if (node["Simulator"]) { 
                const auto& scenariosNode = node["Scenarios"];
                for (const auto& scenarioNode : scenariosNode) {
                    ScenarioDescriptor scenario;

                    //Be sure to add the Simulator and Simulator version also :D
                    scenario.simulator = node["Simulator"].as<std::string>();
                    scenario.simulatorVersion = node["SimVersion"].as<std::string>();

                    Parser::parseScenario(scenarioNode, scenario); //Parse the scenarios
                    std::string scenarioIndex = scenarioNode["Scenario"].as<std::string>(); //We use the Scenario value itself for indexing
                    ScenarioDescriptors[scenarioIndex] = scenario;
                }
            }
        }
    }
}
