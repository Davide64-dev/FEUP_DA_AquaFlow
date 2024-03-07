#include <iostream>
#include <filesystem>
#include "data_structures/graph.h"
#include "City.h"
#include "GraphConstructor.h"

int main() {

    // Print current working directory
    std::cout << "Current Working Directory: " << std::filesystem::current_path() << std::endl;

    GraphConstructor temp = GraphConstructor("../LargeDataSet/Cities.csv", "", "", "");


    Graph<Element> graph = temp.createGraph();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
