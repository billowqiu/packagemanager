cmake_minimum_required(VERSION 3.8)
project(packagemanager)
message("packagemanager CMAKE_SOURCE_DIR is " ${CMAKE_SOURCE_DIR})
message("packagemanager PROJECT_SOURCE_DIR is " ${PROJECT_SOURCE_DIR})
message("packagemanager PROJECT_BINARY_DIR is " ${PROJECT_BINARY_DIR})

file(GLOB SRC_LIST ${PROJECT_SOURCE_DIR}/src/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/deps/)
include_directories(${PROJECT_SOURCE_DIR}/include/)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
add_library(packagemanager ${SRC_LIST})

add_subdirectory(deps/tinyxml)
add_subdirectory(demo/packages)

set(DEMO_SRC ${PROJECT_SOURCE_DIR}/demo/main.cpp)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(demo ${DEMO_SRC})
target_link_libraries(demo packagemanager tinyxml)
