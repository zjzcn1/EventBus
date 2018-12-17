cmake_minimum_required(VERSION 2.8)

project(eventbus)

############ set config ############
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin)
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

############ include ###############
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/demo
)

############ build lib ############
add_library(${PROJECT_NAME} SHARED
        src/EventBus.cpp
        )

############ build exe ############
add_executable(demo
        #        ${COSTMAP_SRC}
        demo/Main.cpp
        )

target_link_libraries(
        demo
        ${PROJECT_NAME}
)