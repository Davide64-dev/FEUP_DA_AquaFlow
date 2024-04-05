//
// Created by Davide Teixeira on 08/03/2024.
//

#include "Manager.h"

Manager::Manager(std::string name) : name(name), constructor(GraphConstructor("../DataSetSmall/Cities_Madeira.csv",
                                                                              "../DataSetSmall/Reservoirs_Madeira.csv",
                                                                              "../DataSetSmall/Stations_Madeira.csv","../DataSetSmall/Pipes_Madeira.csv")){
    this->network = constructor.createGraph();

    this->cities = constructor.getCityMap();

    this->reservoirs = constructor.getReservoirMap();

    this->stations = constructor.getStationMap();

}

void Manager::testAndVisit(std::queue< Vertex<std::string>*> &q, Edge<std::string> *e, Vertex<std::string> *w, double residual) {
    if (! w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

bool Manager::findAugmentingPath(Graph<std::string> *g, Vertex<std::string> *s, Vertex<std::string> *t) {
    // Mark all vertices as not visited
    for(auto v : g->getVertexSet()) { v->setVisited(false);
    }
    // Mark the source vertex as visited and enqueue it
    s->setVisited(true); std::queue<Vertex<std::string> *> q; q.push(s);
    // BFS to find an augmenting path
    while( ! q.empty() && ! t->isVisited()) { auto v = q.front();
        q.pop();
        // Process outgoing edges
        for(auto e: v->getAdj()) {
            testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
        }
        // Process incoming edges
        for(auto e: v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow());
        } }
    // Return true if a path to the target is found, false otherwise
    return t->isVisited();
}

double Manager::findMinResidualAlongPath(Vertex<std::string> *s, Vertex<std::string> *t) {
    double f = INF;
    // Traverse the augmenting path to find the minimum residual capacity
    for (auto v = t; v != s; ) { auto e = v->getPath(); if (e->getDest() == v) {
            f = std::min(f, e->getWeight() - e->getFlow());
            v = e->getOrig(); }
        else {
            f = std::min(f, e->getFlow()); v = e->getDest();
        } }
    // Return the minimum residual capacity
    return f;
}

void Manager::augmentFlowAlongPath(Vertex<std::string> *s, Vertex<std::string> *t, double f) {
    // Traverse the augmenting path and update the flow values accordingly
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else {
            e->setFlow(flow - f); v = e->getDest();
        }
    }
}

void Manager::edmondsKarp(Graph<std::string> *g, std::string source, std::string target) {
    // Find source and target vertices in the graph
    Vertex<std::string>* s = g->findVertex(source); Vertex<std::string>* t = g->findVertex(target);
    // Validate source and target vertices
    if (s == nullptr || t == nullptr || s == t)
        throw std::logic_error("Invalid source and/or target vertex");
    // Initialize flow on all edges to 0
    for (auto v : g->getVertexSet()) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
    // While there is an augmenting path, augment the flow along the path
    while( findAugmentingPath(g, s, t) ) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
    }
}

double Manager::edmondsKarpAllToAll(Graph<std::string>* res){

    Graph<std::string> graph = constructor.createGraph();

    graph.addVertex("supersource");

    for (int i = 0; i < graph.getNumVertex(); i++) {
        if (graph.getVertexSet()[i]->getInfo()[0] == 'R')
            graph.addEdge("supersource", graph.getVertexSet()[i]->getInfo(),
                                       reservoirs.at(graph.getVertexSet()[i]->getInfo()).getMaximumDelivery());
    }


    graph.addVertex("supersink");

    for (int i = 0; i < graph.getNumVertex(); i++) {
        if (graph.getVertexSet()[i]->getInfo()[0] == 'C')
            graph.addEdge(graph.getVertexSet()[i]->getInfo(), "supersink",
                                       cities.at(graph.getVertexSet()[i]->getInfo()).getDemand());
    }

    for (int i = 0; i < graph.getNumVertex(); i++){
        for (int j = 0; j < graph.getVertexSet()[i]->getAdj().size(); j++)
            graph.getVertexSet()[i]->getAdj()[j]->setFlow(0);
    }

    edmondsKarp(&graph, "supersource", "supersink");

    *res = graph;

    int maxflow = 0;
    for (int i = 0; i < graph.getNumVertex(); i++){
        if (graph.getVertexSet()[i]->getInfo()[0] == 'C') {
            for (int j = 0; j < graph.getVertexSet()[i]->getIncoming().size(); j++){
                maxflow += graph.getVertexSet()[i]->getIncoming()[j]->getFlow();
            }
        }
    }

    return maxflow;
}

double Manager::edmondsKarpAllToOne(Graph<std::string>* res, std::string city_code){

    Graph<std::string> graph = constructor.createGraph();

    graph.addVertex("supersource");

    for (int i = 0; i < graph.getNumVertex(); i++) {
        if (graph.getVertexSet()[i]->getInfo()[0] == 'R')
            graph.addEdge("supersource", graph.getVertexSet()[i]->getInfo(),
                          reservoirs.at(graph.getVertexSet()[i]->getInfo()).getMaximumDelivery());
    }

    for (int i = 0; i < graph.getNumVertex(); i++){
        for (int j = 0; j < graph.getVertexSet()[i]->getAdj().size(); j++)
            graph.getVertexSet()[i]->getAdj()[j]->setFlow(0);
    }

    edmondsKarp(&graph, "supersource", city_code);

    *res = graph;

    long maxflow = 0;
    for (int i = 0; i < graph.getNumVertex(); i++){
        if (graph.getVertexSet()[i]->getInfo() == city_code) {
            for (int j = 0; j < graph.getVertexSet()[i]->getIncoming().size(); j++){
                maxflow += graph.getVertexSet()[i]->getIncoming()[j]->getFlow();
            }
        }
    }

    return maxflow;
}
