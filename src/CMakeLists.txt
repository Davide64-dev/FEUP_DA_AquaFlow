cmake_minimum_required(VERSION 3.27)
project(DA_proj1)

set(CMAKE_CXX_STANDARD 17)

add_executable(DA_proj1 main.cpp
        data_structures/Graph.h
        data_structures/City.cpp
        data_structures/City.h
        data_structures/Reservoir.cpp
        data_structures/Reservoir.h
        data_structures/Station.cpp
        data_structures/Station.h
        data_structures/Element.h
        data_structures/GraphConstructor.cpp
        data_structures/GraphConstructor.h
        Manager.cpp
        Manager.h
        Menu.cpp
        Menu.h)
