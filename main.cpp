#include <iostream>
#include <filesystem>
#include "data_structures/graph.h"
#include "City.h"
#include "GraphConstructor.h"

int main() {

    GraphConstructor temp = GraphConstructor("../LargeDataSet/Cities.csv", "../LargeDataSet/Reservoir.csv", "../LargeDataSet/Stations.csv", "");


    Graph<std::string> graph = temp.createGraph();

    for (int i = 0; i< graph.getNumVertex(); i++){
        std::cout << graph.getVertexSet()[i]->getInfo() << std::endl;
    }
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
