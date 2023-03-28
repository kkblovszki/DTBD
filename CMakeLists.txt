# Cmake required version
cmake_minimum_required(VERSION 3.12)

# Project name
project(DTDB)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

# Set the compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Werror") #-Wextra

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

# Link the libraries from the 'libs' directory
link_directories(libs)

# ----------------------------- Add the source files -----------------------------

# Add the source files from the 'src' directory
add_executable(DTDB src/main.cpp)

# Set the output directory for the 'my_project' target to 'bin'
set_target_properties(DTDB PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# ----------------------------- Add Static libraries -----------------------------

add_library(Parser src/Parser.cpp)

add_library(DTDB_framework 
            src/core.Testbed.cpp 
            src/core.Scenario.cpp 
            src/core.Benchmark.cpp
            src/ListenerCreator.cpp
            src/SimulatorCreator.cpp
            )

add_library(DTDB_listeners 
            src/Listeners/DefaultListener.cpp
            src/Listeners/TestListener.cpp
            )

set_target_properties(DTDB_framework PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/static_libs")
set_target_properties(DTDB_listeners PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/static_libs")

set(CMAKE_FRAMEWORK_CPP_PATH ${CMAKE_FRAMEWORK_CPP_PATH} "${CMAKE_SOURCE_DIR}/src")
set(FRAMEWORK_CPP_INCLUDE_DIR ${FRAMEWORK_CPP_INCLUDE_DIR} "${CMAKE_FRAMEWORK_CPP_PATH}/include")

# Link the libraries
target_link_libraries(DTDB_framework Parser)
target_link_libraries(DTDB_framework DTDB_listeners)

# Link the libraries to the executables
target_link_libraries(DTDB DTDB_framework)

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

set_target_properties(NS3Simulator PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/shared_libs")          
target_link_libraries(NS3Simulator yaml-cpp)

# ------------------------------- Add the tests -------------------------------

# Add any test files from the 'test' directory
add_executable(NS3_Exhaustive_scenario_creation test/NS3_Tests/NS3_ScenarioCreationExhaustive.cpp)
add_executable(NS3_Basic_scenario_creation test/NS3_Tests/NS3_ScenarioCreationBasic.cpp)

# Set the output directory for the 'my_project_tests' target to 'test/bin'
set_target_properties(NS3_Basic_scenario_creation NS3_Exhaustive_scenario_creation PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests")

target_link_libraries(NS3_Exhaustive_scenario_creation DTDB_framework)
target_link_libraries(NS3_Basic_scenario_creation DTDB_framework)

