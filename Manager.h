//
// Created by Davide Teixeira on 08/03/2024.
//

#ifndef DA_PROJ1_MANAGER_H
#define DA_PROJ1_MANAGER_H

#include <string>
#include "data_structures/Graph.h"
#include <unordered_map>
#include "data_structures/City.h"
#include "data_structures/Reservoir.h"
#include "data_structures/Station.h"
#include "data_structures/GraphConstructor.h"

class Manager {
private:
    std::string name;
    GraphConstructor constructor;
public:
    Graph<std::string> network;
    std::unordered_map<std::string, City> cities;
    std::unordered_map<std::string, Reservoir> reservoirs;
    std::unordered_map<std::string, Station> stations;
    Manager(std::string name = "FEUPAquaFlow");

    void testAndVisit(std::queue< Vertex<std::string>*> &q, Edge<std::string> *e, Vertex<std::string> *w, double residual);

    bool findAugmentingPath(Graph<std::string> *g, Vertex<std::string> *s, Vertex<std::string> *t);

    double findMinResidualAlongPath(Vertex<std::string> *s, Vertex<std::string> *t);

    void augmentFlowAlongPath(Vertex<std::string> *s, Vertex<std::string> *t, double f);

    void edmondsKarp(Graph<std::string> *g, std::string source, std::string target);

    double edmondsKarpAllToAll(Graph<std::string>* res);

    double edmondsKarpAllToOne(Graph<std::string>* res, std::string city_code);
};


#endif //DA_PROJ1_MANAGER_H
