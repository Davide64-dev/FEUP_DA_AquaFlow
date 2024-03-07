//
// Created by Davide Teixeira on 07/03/2024.
//

#ifndef DA_PROJ1_GRAPHCONSTRUCTOR_H
#define DA_PROJ1_GRAPHCONSTRUCTOR_H

#include "data_structures/graph.h"
#include "Element.h"
#include "City.h"
#include "Station.h"
#include "Reservoir.h"
#include <string>

class GraphConstructor {
private:
    std::string citiesFile;
    std::string reservoirsFile;
    std::string stationsFile;
    std::string pipesFile;

    City parseCity(std::string line);
    Reservoir parseReservoir(std::string line);
    Station parseStation(std::string line);
    void addNodes(Graph<Element>& graph);
    void addEdges(Graph<Element>& graph);

public:
    GraphConstructor(std::string citiesFile, std::string reservoirsFile, std::string stationsFile, std::string pipesFile);
    Graph<std::string> createGraph();

};


#endif //DA_PROJ1_GRAPHCONSTRUCTOR_H
