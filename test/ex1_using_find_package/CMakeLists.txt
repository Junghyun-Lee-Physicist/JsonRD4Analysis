cmake_minimum_required(VERSION 3.10)
project(JsonLibTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED ENV{JsonRD_LIB_ROOT})
  message(FATAL_ERROR "JsonRD_LIB_ROOT environment variable is not set. Please source JsonRDsetup.sh")
endif()

find_package(JsonRD4Analysis REQUIRED)

add_executable(test_json test_json.cpp)

target_link_libraries(test_json PRIVATE JsonRD4Analysis::JsonRD4Analysis)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/config.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
