# Cmake required version
cmake_minimum_required(VERSION 3.12)

# Project name
project(DTDB)

#debug mode
add_definitions(-DDEBUG)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wno-unused-value") #-Wextra -Werror

# ------------------------------- Add the Doxygen documentation -------------------------------
find_package(Doxygen REQUIRED)

option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()

    set(doxyfile    ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)

    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_MAN YES)

    doxygen_add_docs(
            doxygen
            ${CMAKE_CURRENT_SOURCE_DIR}/src
            COMMENT "Generate code documentation."
    )

    add_custom_target(doc ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)

    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc)
endif()

# ---------------------------------------------------------------------------------------------

# Include the header files from the 'include' directory
include_directories(src/include)

# Define the path to the SMI directory as a variable to use in the code
add_definitions(-DSMI_PATH="${CMAKE_SOURCE_DIR}/SMIs")

add_definitions(-DRESULTS_PATH="${CMAKE_BINARY_DIR}/bin") #TODO: Find a better solution to store results from simulators.

# Link the libraries from the 'libs' directory
link_directories(libs)

# ----------------------------- Add the source files -----------------------------

# Add the source files from the 'src' directory
add_executable(DTDB src/main.cpp)

# Set the output directory for the 'my_project' target to 'bin'
set_target_properties(DTDB PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# ----------------------------- Add Static libraries -----------------------------


add_library(DTDB_framework 
            src/core.Testbed.cpp 
            src/core.Scenario.cpp 
            src/core.Benchmark.cpp
            src/ListenerCreator.cpp
            src/SimulatorCreator.cpp
            src/Parser.cpp
            )

#add_library(Parser )

add_library(DTDB_listeners 
            src/Listeners/ConsoleListener.cpp
            src/Listeners/CSVListener.cpp
            src/Listeners/TestListener.cpp
            )

set_target_properties(DTDB_framework PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/static_libs")
set_target_properties(DTDB_listeners PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/static_libs")

set(CMAKE_FRAMEWORK_CPP_PATH ${CMAKE_FRAMEWORK_CPP_PATH} "${CMAKE_SOURCE_DIR}/src")
set(FRAMEWORK_CPP_INCLUDE_DIR ${FRAMEWORK_CPP_INCLUDE_DIR} "${CMAKE_FRAMEWORK_CPP_PATH}/include")

# Link the libraries
target_link_libraries(DTDB_framework ${CMAKE_DL_LIBS})
target_link_libraries(DTDB_framework DTDB_listeners)

# Link the libraries to the executables
target_link_libraries(DTDB DTDB_framework)

# ------------ Basic Commandline interface ------------

add_executable(DTDB_cli src/CLI/DTDB_CLI.cpp)

set_target_properties(DTDB_cli PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/cli")

target_link_libraries(DTDB_cli DTDB_framework)


# ------------------------------- Yaml-cpp -----------------------------

set(CMAKE_YAML_CPP_PATH ${CMAKE_YAML_CPP_PATH} "${CMAKE_SOURCE_DIR}/libs/yaml-cpp")
set(YAML_CPP_INCLUDE_DIR ${YAML_CPP_INCLUDE_DIR} "${CMAKE_YAML_CPP_PATH}/include")

set(YAML_CPP_BUILD_TESTS OFF CACHE INTERNAL "")

add_subdirectory(libs/yaml-cpp)
include_directories(${YAML_CPP_SOURCE_DIR}/include)

target_link_libraries(DTDB_framework yaml-cpp)

# ----------------------------- Add Shared libraries -----------------------------


add_library(NS3Simulator SHARED 
            src/Wrappers/NS3/NS3_SMI.cpp
            )


#ensure there exists a 32-bit offset, so that the shared library can be loaded at any address in memory.POSITION_INDEPENDENT_CODE ON
set_target_properties(NS3Simulator PROPERTIES POSITION_INDEPENDENT_CODE ON LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/shared_libs")

target_link_libraries(NS3Simulator yaml-cpp)

# ------------------------------- Add the tests -------------------------------

# ------------ Framework tests ------------

add_executable(LoadSimConfig test/Framework_tests/load_sim_config.cpp)
add_executable(CreateBenchmark test/Framework_tests/create_benchmark.cpp)
add_executable(SharedLibLoad test/Framework_tests/test_shared_lib_load.cpp)
add_executable(PersistentDataMatchingTest test/Framework_tests/check_persistent_data_loaded.cpp)
add_executable(RunScenario test/Framework_tests/test_run_scenario.cpp)

# Set the output directory for the 'my_project_tests' target to 'test/bin'
set_target_properties(LoadSimConfig PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests/framework_tests")
set_target_properties(CreateBenchmark PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests/framework_tests")
set_target_properties(SharedLibLoad PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests/framework_tests")
set_target_properties(PersistentDataMatchingTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests/framework_tests")
set_target_properties(RunScenario PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests/framework_tests")

target_link_libraries(LoadSimConfig DTDB_framework)
target_link_libraries(CreateBenchmark DTDB_framework)
target_link_libraries(SharedLibLoad DTDB_framework)
target_link_libraries(PersistentDataMatchingTest DTDB_framework)
target_link_libraries(RunScenario DTDB_framework)

add_test(NAME LoadSimConfig COMMAND LoadSimConfig)
add_test(NAME CreateBenchmark COMMAND CreateBenchmark)
add_test(NAME SharedLibLoad COMMAND SharedLibLoad)
add_test(NAME PersistentDataMatchingTest COMMAND PersistentDataMatchingTest)
add_test(NAME RunScenario COMMAND RunScenario)


# ------------ NS3 tests ------------

add_executable(RunNS3Tutorial test/NS3_Tests/NS3_run_tests/Test_run_tutorial.cpp)

set_target_properties(RunNS3Tutorial PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests/NS3_tests")

target_link_libraries(RunNS3Tutorial DTDB_framework)

add_test(NAME RunNS3Tutorial COMMAND RunNS3Tutorial)


if(COMPILE_TESTS)

# Add any test files from the 'test' directory
add_executable(NS3_Exhaustive_scenario_creation test/NS3_Tests/NS3_ScenarioCreationExhaustive.cpp)
add_executable(NS3_Basic_scenario_creation test/NS3_Tests/NS3_ScenarioCreationBasic.cpp)

# Set the output directory for the 'my_project_tests' target to 'test/bin'
set_target_properties(NS3_Basic_scenario_creation NS3_Exhaustive_scenario_creation PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests/NS3_tests")

target_link_libraries(NS3_Exhaustive_scenario_creation DTDB_framework)
target_link_libraries(NS3_Basic_scenario_creation DTDB_framework)

# Add tests that will be run when running the 'make test' command
add_test(NAME NS3_Exhaustive_scenario_creation_test COMMAND NS3_Exhaustive_scenario_creation)
add_test(NAME NS3_Basic_scenario_creation_test COMMAND NS3_Basic_scenario_creation)

endif()
# ------------ YAML parser tests ------------

# Add tests from the directory
add_executable(parser_test test/parser_tests/parserTests.cpp)
add_executable(parser_unit_tests test/parser_tests/parserUnitTests.cpp)

# Set the output directory for the 'my_projects_tests' target to 'test/bin'
set_target_properties(parser_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests/parser_tests")
set_target_properties(parser_unit_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests/parser_unit_tests")

# Link the parser directory with the main framework
target_link_libraries(parser_test DTDB_framework)
target_link_libraries(parser_unit_tests DTDB_framework)

# Add the test to the test suite
add_test(NAME parser_test COMMAND parser_test)
add_test(NAME parser_unit_tests COMMAND parser_unit_tests)


