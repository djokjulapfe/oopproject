cmake_minimum_required(VERSION 3.9)
project(oopproject)

set(CMAKE_CXX_STANDARD 11)

add_executable(oopproject main.cpp SimulationEngine/Event.cpp SimulationEngine/Event.h SimulationEngine/types.h SimulationEngine/Interfaces.h SimulationEngine/Scheduler.cpp SimulationEngine/Scheduler.h SimulationEngine/SimulationEngine.h)