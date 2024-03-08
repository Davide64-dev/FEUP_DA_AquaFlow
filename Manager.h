//
// Created by Davide Teixeira on 08/03/2024.
//

#ifndef DA_PROJ1_MANAGER_H
#define DA_PROJ1_MANAGER_H

#include <string>
#include "data_structures/Graph.h"
#include <unordered_map>
#include "City.h"
#include "Reservoir.h"
#include "Station.h"
#include "GraphConstructor.h"

class Manager {
private:
    std::string name;
public:
    Graph<std::string> network;
    std::unordered_map<std::string, City> cities;
    std::unordered_map<std::string, Reservoir> reservoirs;
    std::unordered_map<std::string, Station> stations;
    Manager(std::string name = "FEUPAquaFlow");
};


#endif //DA_PROJ1_MANAGER_H
