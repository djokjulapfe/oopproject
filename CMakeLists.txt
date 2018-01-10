cmake_minimum_required(VERSION 3.9)
project(oopproject)

set(CMAKE_CXX_STANDARD 11)

add_executable(oopproject main.cpp SimulationEngine/Event.cpp SimulationEngine/Event.h Utils/types.h Utils/Interfaces.h SimulationEngine/Scheduler.cpp SimulationEngine/Scheduler.h SimulationEngine/SimulationEngine.h Hardware/Token.cpp Hardware/Token.h Hardware/Operation.cpp Hardware/Operation.h Visitor/Visitor.cpp Visitor/Visitor.h Hardware/Model.cpp Hardware/Model.h Software/Expression.cpp Software/Expression.h Software/Program.cpp Software/Program.h Software/Compiler.cpp Software/Compiler.h Software/Machine.cpp Software/Machine.h Software/Memory.cpp Software/Memory.h Hardware/ArithmeticOperation.cpp Hardware/ArithmeticOperation.h Hardware/AddOperation.cpp Hardware/AddOperation.h Hardware/MultOperation.cpp Hardware/MultOperation.h)