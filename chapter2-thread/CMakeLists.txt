cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(chapter2-thread VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CONFIGURATION_TYPES Release;Debug)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_executable(chapter2-thread "${CMAKE_CURRENT_SOURCE_DIR}/src.cpp")
target_include_directories(chapter2-thread PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(chapter2-thread PUBLIC cxx_std_17)