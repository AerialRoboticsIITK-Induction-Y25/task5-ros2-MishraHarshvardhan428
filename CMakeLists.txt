cmake_minimum_required(VERSION 3.10)

project(drone_fleet)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(
    -Wall
    -Wextra
)

include_directories(include)

add_executable(test_oop

    src/main.cpp
    src/Vehicle.cpp
    src/Drone.cpp
    src/MissionDrone.cpp
    src/AutonomousDrone.cpp
)