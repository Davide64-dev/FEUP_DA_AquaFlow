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
            auto nextVertex = currentVertex->getAdj()[i];
            if (nextVertex->getWeight() - nextVertex->getFlow() > 0 && !nextVertex->getDest()->isVisited()){
                nextVertex->getDest()->setPath(nextVertex);
                q.push(nextVertex->getDest()->getInfo());
            }
        }

        for (int i = 0; i < currentVertex->getIncoming().size(); i++){
            auto nextVertex = currentVertex->getIncoming()[i];
            if (nextVertex->getFlow() > 0 && !nextVertex->getDest()->isVisited()){
                nextVertex->getDest()->setPath(nextVertex);
                q.push(nextVertex->getOrig()->getInfo());
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
        //std::cout << "Path found!" << std::endl;
        int min = INT_MAX;

        T v = supersink;

        while (v != supersource){
            //std::cout << v << std::endl;

            auto currentVertex = graph.findVertex(v);

            if (currentVertex->getPath()->getWeight() < min) min = currentVertex->getPath()->getWeight();
            v = graph.findVertex(v)->getPath()->getOrig()->getInfo();
        }

        v = supersink;

        while (v != supersource){
            auto currentVertex = graph.findVertex(v);

            currentVertex->getPath()->setFlow(currentVertex->getPath()->getFlow() + min);

            v = graph.findVertex(v)->getPath()->getOrig()->getInfo();
        }

    }

    for (int i = 0; i < graph.getVertexSet().size(); i++){
        double VertexIncoming = 0;
        for (int j = 0; j < graph.getVertexSet()[i]->getIncoming().size(); j++){
            VertexIncoming += graph.getVertexSet()[i]->getIncoming()[j]->getFlow();
        }
        graph.getVertexSet()[i]->setMaxIncoming(VertexIncoming);
    }

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
            for (int i = 0; i < manager.network.getNumVertex(); i++){
                if (manager.network.getVertexSet()[i]->getInfo()[0] == 'C') {
                    std::cout << manager.network.getVertexSet()[i]->getInfo();
                    std::cout << " -> ";
                    std::cout << manager.network.getVertexSet()[i]->getMaxIncoming() << std::endl;
                }
            }
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