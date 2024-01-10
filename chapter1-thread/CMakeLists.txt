cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(chapter1-thread VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CONFIGURATION_TYPES Release;Debug)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_executable(chapter1-thread "${CMAKE_CURRENT_SOURCE_DIR}/src.cpp")
target_include_directories(chapter1-thread PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(chapter1-thread PUBLIC cxx_std_17)