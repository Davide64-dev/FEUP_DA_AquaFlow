//
// Created by anacr on 29/03/2024.
//

#include "Algorithms.h"
#include "Reservoir.h"
#include "City.h"
#include "Manager.h"
#include <queue>



void t21(Manager manager){
    std::cout << "teste..." << std::endl;

    int option = 0;
    std::cout << "Maximum amount of water that can reach..." << std::endl;
    std::cout << "1 - Each city" << std::endl;
    std::cout << "2 - A specific city" << std::endl;
    std::cout << "\nChoose an option:";
    std::cin >> option;

    int maxflow = 0;
    Graph<std::string> graph;
    switch (option) {
        case 1:
            std::cout << "Each city" << std::endl;
            manager.edmondsKarpAllToAll(&graph);
            for (int i = 0; i < graph.getNumVertex(); i++){
                if (graph.getVertexSet()[i]->getInfo()[0] == 'C') {
                    std::cout << graph.getVertexSet()[i]->getInfo();
                    std::cout << " -> ";
                    int temp = 0;
                    for (int j = 0; j < graph.getVertexSet()[i]->getIncoming().size(); j++){
                        temp += graph.getVertexSet()[i]->getIncoming()[j]->getFlow();
                    }
                    maxflow += temp;
                    std::cout << temp << std::endl;
                }
            }
            std::cout << "Max flow: " << maxflow << std::endl;
            break;
        case 2:
            std::cout << "A specific city" << std::endl;
            std::cout << "TO-DO" << std::endl;
            break;
        default:
            std::cout << "Invalid option" << std::endl;
            break;
    }


    // TO ELIMINATE IN THE FUTURE
    //std::cout << "Edmonds-Karp algorithm example" << std::endl;
    //Vertex source = graph.getVertexSet()[0];
    //Vertex sink = graph.network.getVertexSet()[5];
    //std::cout << "Max flow: " << edmondsKarp(graph.network, source, sink) << std::endl;
}