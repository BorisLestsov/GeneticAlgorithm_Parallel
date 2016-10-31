cmake_minimum_required(VERSION 2.5)
project(Gen)

set(CMAKE_CXX_COMPILER mpicxx)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(INCLUDE_DIR "include")
set(SOURCE_DIR "src")

file(GLOB SOURCE_FILES
        "${SOURCE_DIR}/*.cpp"
        "${INCLUDE_DIR}/*.h"
        "${INCLUDE_DIR}/*.hpp"
)

include_directories(${INCLUDE_DIR})

add_executable(Gen ${SOURCE_FILES})


set_target_properties(Gen PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_SOURCE_DIR}/bin
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin
        )