# Cmake required version
cmake_minimum_required(VERSION 3.12)

# Project name
project(DTDB)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

# Set the compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Werror -v") #-Wextra

#Add the shared libraries
#add_library(DTDB_Framework SHARED src/handlers/Handler.cpp src/handlers/Handler.h)

# Set the output directory for the 'my_project' target to 'bin'
#set_target_properties(DTDB_Framework PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/shared_libs")

# ------------------------------- Add the Doxygen documentation -------------------------------
find_package(Doxygen REQUIRED)

option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()

    #set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
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

#add_executable(DTDB_sims src/Wrappers/NS3/NS3Interface.cpp)
#add_executable(DTDB_additional src/SimulatorCreator.cpp src/ListenerCreator.cpp)src/core.Scenario.cpp src/core.Benchmark.cpp

# Set the output directory for the 'my_project' target to 'bin'
set_target_properties(DTDB PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
#set_target_properties(DTDB_sims PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/simulators/bin")
#set_target_properties(DTDB_additional PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# ------------------------------- Add the tests -------------------------------

# Add any test files from the 'test' directory
add_executable(DTDB_tests test/scenarioCreationBasic.cpp)

# Set the output directory for the 'my_project_tests' target to 'test/bin'
set_target_properties(DTDB_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests")


# ----------------------------- Add Static libraries -----------------------------

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

# Link the libraries
target_link_libraries(DTDB_framework DTDB_listeners)

# Link the libraries to the executables
target_link_libraries(DTDB DTDB_framework)
target_link_libraries(DTDB_tests DTDB_framework)

# ----------------------------- Add Shared libraries -----------------------------

#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/shared_lib)

add_library(NS3Simulator SHARED 
            src/Wrappers/NS3/NS3_SMI.cpp
            )

set_target_properties(NS3Simulator PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/shared_libs")          
