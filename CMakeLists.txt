# Cmake required version
cmake_minimum_required(VERSION 3.12)

# Project name
project(DTDB_Framework)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

# Set the compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

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
include_directories(include)

# Link the libraries from the 'libs' directory
link_directories(libs)

# Include the header files from the 'include' directory
include_directories(include)

# ----------------------------- Add the source files -----------------------------

# Add the source files from the 'src' directory
add_executable(DTDB_main src/main.cpp)
add_executable(DTDB_core src/core.Benchmark.cpp src/core.Scenario.cpp src/core.Testbed.cpp)
add_executable(DTDB_additional src/SimulatorCreator.cpp src/SimulatorListener.cpp)

# Set the output directory for the 'my_project' target to 'bin'
set_target_properties(DTDB_main PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set_target_properties(DTDB_core PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set_target_properties(DTDB_additional PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")


# ------------------------------- Add the tests -------------------------------

# Add any test files from the 'test' directory
add_executable(DTDB_tests test/add_test.cpp)

# Set the output directory for the 'my_project_tests' target to 'test/bin'
set_target_properties(DTDB_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests/bin")


