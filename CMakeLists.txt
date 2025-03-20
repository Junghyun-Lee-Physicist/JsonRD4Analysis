

cmake_minimum_required(VERSION 3.10)
project(JsonRD4Analysis VERSION 1.0 LANGUAGES CXX)


# Set the default installation directory if not specified by the user.
# This sets CMAKE_INSTALL_PREFIX to the "install" folder in the source directory.
if(NOT DEFINED CMAKE_INSTALL_PREFIX OR CMAKE_INSTALL_PREFIX STREQUAL "/usr/local")
  set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE PATH "Installation Directory" FORCE)
endif()

# Option: Build as a shared library (ON) or static library (OFF)
option(BUILD_SHARED_LIBS "Build as a shared library (OFF for static)" ON)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Build the library target from source
add_library(JsonRD4Analysis
    src/JsonConfigReader.cpp
)


# Set the include directories for the JsonRD4Analysis target:
# - Use the source tree "include" directory during build.
# - Use the installed "include" directory when the library is installed.
target_include_directories(JsonRD4Analysis
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)


# Installation settings:
# - Install the JsonRD4Analysis target.
# - Export target information for find_package() usage.
# - Place static libraries (ARCHIVE) and shared libraries (LIBRARY) in the "lib" folder.
install(TARGETS JsonRD4Analysis
    EXPORT JsonRD4Analysis-targets
    ARCHIVE DESTINATION lib # For static libraries
    LIBRARY DESTINATION lib # For shared libraries
)


# Install header files in the include folder
install(DIRECTORY include/ DESTINATION include)


# Install the exported targets file.
# This creates a file (JsonRD4Analysis-targets.cmake) that contains all information about the exported targets
# (such as include directories, compile options, etc.), which can be used by other projects via find_package().
# The NAMESPACE option prepends "JsonRD4Analysis::" to all target names when they are imported.
install(EXPORT JsonRD4Analysis-targets 
    FILE JsonRD4Analysis-targets.cmake
    NAMESPACE JsonRD4Analysis::
    DESTINATION share/JsonRD4Analysis/cmake
)


# Generate and install the package configuration file.
# The package configuration file (JsonRD4AnalysisConfig.cmake) is used by find_package(JsonRD4Analysis) in
# external projects to locate and correctly configure the JsonRD4Analysis package.
# We include CMakePackageConfigHelpers to enable special placeholders (such as @PACKAGE_INIT@) in the template.
include(CMakePackageConfigHelpers) 
#   --> Enables use of special placeholders like @PACKAGE_INIT@ in the config template.
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/JsonRD4AnalysisConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/JsonRD4AnalysisConfig.cmake"
    INSTALL_DESTINATION share/JsonRD4Analysis/cmake 
)


# Install the generated package configuration file to the proper directory.
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/JsonRD4AnalysisConfig.cmake"
    DESTINATION share/JsonRD4Analysis/cmake
)


# Generate and install the environment setup script.
# The setup script is used to configure environment variables (e.g., JSONLIB_ROOT, CPATH, LD_LIBRARY_PATH) for users.
# We use configure_file() with the @ONLY option so that only @VAR@ placeholders are replaced,
# while ${...} shell variable syntax is preserved for runtime expansion.
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/JsonRDsetup.sh.in"
               "${CMAKE_CURRENT_BINARY_DIR}/JsonRDsetup.sh" 
	       @ONLY
)


# Install the generated setup script to the package's share directory.
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/JsonRDsetup.sh"
        DESTINATION share/JsonRD4Analysis
)


