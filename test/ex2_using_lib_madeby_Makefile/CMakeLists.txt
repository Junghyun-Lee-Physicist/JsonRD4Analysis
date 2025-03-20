cmake_minimum_required(VERSION 3.13)
project(JsonLibTest)

# Set the C++ standard to C++17.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check that the JsonRD_LIB_ROOT environment variable is set.
# This variable should be configured via an environment setup script (e.g., JsonRDsetup.sh)
# and points to the installation directory of the library.
if(NOT DEFINED ENV{JsonRD_LIB_ROOT})
  message(FATAL_ERROR "JsonRD_LIB_ROOT environment variable is not set. Please source JsonRDsetup.sh")
endif()

# Set the JsonRD_LIB_ROOT variable from the environment.
set(JsonRD_LIB_ROOT $ENV{JsonRD_LIB_ROOT})

# Create the test executable target.
add_executable(test_json test_json.cpp)

### Modern CMake: Specify include directories for the test target.
### This is analogous to setting CPATH at compile time.
##target_include_directories(test_json PRIVATE ${JsonRD_LIB_ROOT}/include)
##
### Modern CMake (since 3.13): Specify library search directories for linking.
### This is similar to setting LIBRARY_PATH at build time.
##target_link_directories(test_json PRIVATE ${JsonRD_LIB_ROOT}/lib)

# Link the test target with the JsonRD4Analysis library.
# It is assumed that the library (e.g., libJsonRD4Analysis.so or libJsonRD4Analysis.a) 
# exists in the JsonRD_LIB_ROOT/lib directory.

target_link_libraries(test_json PRIVATE JsonRD4Analysis)

# We already set the LIBRARY_PATH or DYLD_LIBRARY_PATH, So CMake directly search the libraries at that paths.
# But you can also set the libraries link like below
#   -->  target_link_libraries(test_json PRIVATE <install>/lib/libJsonRD4Analysis.so)

# Copy the input.json file from the source directory to the binary directory.
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/config.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
