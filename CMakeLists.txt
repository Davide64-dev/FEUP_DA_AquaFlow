cmake_minimum_required(VERSION 3.27)
project(DA_proj1)

set(CMAKE_CXX_STANDARD 17)

add_executable(DA_proj1 main.cpp
        data_structures/Graph.h
        City.cpp
        City.h
        Reservoir.cpp
        Reservoir.h
        Station.cpp
        Station.h
        Element.h
        GraphConstructor.cpp
        GraphConstructor.h
        Manager.cpp
        Manager.h
        Algorithms.h
        Algorithms.cpp)
