//
// Created by anacr on 29/03/2024.
//

#include "Algorithms.h"
#include "Reservoir.h"
#include "City.h"
#include "Manager.h"
#include <queue>


template <class T>
bool findAugmentingPath(Graph<T>& graph, T source, T sink){
    for (int i = 0; i < graph.getNumVertex(); i++){
        graph.getVertexSet()[i]->setVisited(false);
    }
    std::queue<T> q;
    graph.findVertex(source)->setVisited(true);
    q.push(source);

    while (!q.empty()){
        T current = q.front();
        q.pop();
        auto currentVertex = graph.findVertex(current);
        currentVertex->setVisited(true);
        for (int i = 0; i < currentVertex->getAdj().size(); i++){
            if (currentVertex->getAdj()[i]->getWeight() - currentVertex->getAdj()[i]->getFlow() > 0 && !currentVertex->getAdj()[i]->getDest()->isVisited()){
                currentVertex->setPath(currentVertex->getAdj()[i]);
                q.push(currentVertex->getAdj()[i]->getDest()->getInfo());
            }
        }
        for (int i = 0; i < currentVertex->getIncoming().size(); i++){
            if (currentVertex->getIncoming()[i]->getFlow() > 0 && !currentVertex->getAdj()[i]->getDest()->isVisited()){
                currentVertex->setPath(currentVertex->getAdj()[i]);
                q.push(currentVertex->getIncoming()[i]->getOrig()->getInfo());
            }
        }
    }

    return graph.findVertex(sink)->isVisited();

}




template <class T>
int edmondsKarp(Graph<T>& graph, std::unordered_map<std::string, Reservoir>& reservoirs, std::unordered_map<std::string, City>& cities) {

    T supersource = "supersource";

    graph.addVertex(supersource);

    for (int i = 0; i < graph.getNumVertex(); i++) {
        if (graph.getVertexSet()[i]->getInfo()[0] == 'R')
            graph.addBidirectionalEdge(supersource, graph.getVertexSet()[i]->getInfo(),
                                       reservoirs.at(graph.getVertexSet()[i]->getInfo()).getMaximumDelivery());
    }

    T supersink = "supersink";

    graph.addVertex(supersink);

    for (int i = 0; i < graph.getNumVertex(); i++) {
        if (graph.getVertexSet()[i]->getInfo()[0] == 'C')
            graph.addBidirectionalEdge(graph.getVertexSet()[i]->getInfo(), supersink,
                                       cities.at(graph.getVertexSet()[i]->getInfo()).getDemand());
    }

    for (int i = 0; i < graph.getNumVertex(); i++){
        for (int j = 0; j < graph.getVertexSet()[i]->getAdj().size(); j++)
            graph.getVertexSet()[i]->getAdj()[j]->setFlow(0);
    }

    int max_flow = 0;

    while (findAugmentingPath(graph, supersource, supersink)) {
        std::cout << "Path found!" << std::endl;
        /*
        for (T v = supersink; v != supersource; v = parent[v]) {
            std::cout << "In first for cycle" << std::endl;
            T u = parent[v];
            path_flow = std::min(path_flow, residual[u][v]);
        }

        for (T v = supersink; v != supersource; v = parent[v]) {
            std::cout << "In second for cycle" << std::endl;
            T u = parent[v];
            residual[u][v] -= path_flow;
            residual[v][u] += path_flow;
        }
         */

        //max_flow += path_flow;
        std::cout << "Max flow: " << max_flow << std::endl;
    }

    std::cout << "Max flow: " << max_flow << std::endl;
    return max_flow;

}


void t21(Manager manager){
    std::cout << "teste..." << std::endl;

    int option = 0;
    std::cout << "Maximum amount of water that can reach..." << std::endl;
    std::cout << "1 - Each city" << std::endl;
    std::cout << "2 - A specific city" << std::endl;
    std::cout << "\nChoose an option:";
    std::cin >> option;

    switch (option) {
        case 1:
            std::cout << "Each city" << std::endl;
            edmondsKarp(manager.network, manager.reservoirs, manager.cities);
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