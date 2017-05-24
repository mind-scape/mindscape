cmake_minimum_required(VERSION 3.0.2)
project(mindscape)

# Creating variables

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(ASSETS "${PROJECT_SOURCE_DIR}/assets")
set(ENGINE "${PROJECT_SOURCE_DIR}/engine")
file(GLOB SOURCES "${SRC_DIR}/*.cpp")

# Setting COMPILE_FLAGS (this is from CMAKE)

set(COMPILE_FLAGS "-std=c++11 -W -std=c++0x -Wall -pedantic -Wshadow -O2 -g")

# Adding subdirectory which has it's own CMakeList
add_subdirectory(${ENGINE})

# Including header files

include_directories(${INCLUDE_DIR})

# Creating executable and adding libraries to CMake

add_executable(mindscape ${SOURCES})
set_property(TARGET mindscape PROPERTY CXX_STANDARD 11)
target_link_libraries(mindscape engine SDL2 SDL2_image SDL2_ttf SDL2_mixer)
