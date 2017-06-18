file(GLOB SRC_LIST *.cpp)
message("demo CMAKE_SOURCE_DIR is " ${CMAKE_SOURCE_DIR})
message("demo PROJECT_SOURCE_DIR is " ${PROJECT_SOURCE_DIR})
message("demo is " ${PROJECT_BINARY_DIR})

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
include_directories(${PROJECT_SOURCE_DIR}/include/)
add_library(commpackage SHARED ${SRC_LIST})
