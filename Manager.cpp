//
// Created by Davide Teixeira on 08/03/2024.
//

#include "Manager.h"


Manager::Manager(bool isSmallDataSet, std::string name) : name(name){

    if (isSmallDataSet)
        this->constructor = GraphConstructor("../Project1DataSetSmall/Cities_Madeira.csv",
                                                                              "../Project1DataSetSmall/Reservoirs_Madeira.csv",
                                                                              "../Project1DataSetSmall/Stations_Madeira.csv","../Project1DataSetSmall/Pipes_Madeira.csv", isSmallDataSet);
    else
        this->constructor = GraphConstructor("../LargeDataSet/Cities.csv", "../LargeDataSet/Reservoir.csv",
                                             "../LargeDataSet/Stations.csv", "../LargeDataSet/Pipes.csv", isSmallDataSet);

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
    while( ! q.empty() && ! t->isVisited()) {
        auto v = q.front();
        q.pop();
        if (!v->isActiveted()) continue;
        // Process outgoing edges
        for(auto e: v->getAdj()) {
            if (!e->isActivated()) {
                std::cout << "Deactivated edge, ignore!" << std::endl;
                continue;
            }

            testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
        }
        // Process incoming edges
        for(auto e: v->getIncoming()) {
            if (!e->isActivated()){
                continue;
            }
            testAndVisit(q, e, e->getOrig(), e->getFlow());
        } }
    // Return true if a path to the target is found, false otherwise
    return t->isVisited();
}

double Manager::findMinResidualAlongPath(Vertex<std::string> *s, Vertex<std::string> *t) {
    double f = INF;
    // Traverse the augmenting path to find the minimum residual capacity
    for (auto v = t; v != s; ) {
        auto e = v->getPath();

        if (!e->isActivated()){
            std::cout << "Something really weird" << std::endl;
        }
        if (e->getDest() == v) {
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
        if (!e->isActivated()){
            std::cout << "Something really weird" << std::endl;
        }
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
            if (!e->isActivated()){
                std::cout << "Edge not activated" << std::endl;
            }
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

    addSupersourceAndSuperSink(graph);

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

void Manager::balanceFlow(Graph<std::string>* graph) {
    // Identify nodes with unmet demand
    std::vector<Vertex<std::string>*> nodesWithUnmetDemand;
    for (Vertex<std::string>* vertex : graph->getVertexSet()) {
        if (vertex->getInfo()[0] == 'C') {
            double demand = this->cities.at(vertex->getInfo()).getDemand();
            double totalInflow = 0;
            for (Edge<std::string>* edge : vertex->getIncoming()) {
                totalInflow += edge->getFlow();
            }
            if (totalInflow < demand) {
                nodesWithUnmetDemand.push_back(vertex);
            }
        }
    }

    // Calculate excess capacity for each pipe
    std::unordered_map<Edge<std::string>*, double> excessCapacity;
    double totalExcessCapacity = 0;
    for (Vertex<std::string>* vertex : graph->getVertexSet()) {
        for (Edge<std::string>* edge : vertex->getAdj()) {
            double capacity = edge->getWeight();
            double flow = edge->getFlow();
            double remainingCapacity = capacity - flow;
            if (remainingCapacity > 0) {
                excessCapacity[edge] = remainingCapacity;
                totalExcessCapacity += remainingCapacity;
            }

        }
    }

    // Redistribute flow
    for (Vertex<std::string>* vertex : nodesWithUnmetDemand) {
        double demand = this->cities.at(vertex->getInfo()).getDemand();
        double totalInflow = 0;
        for (Edge<std::string>* edge : vertex->getIncoming()) {
            totalInflow += edge->getFlow();
        }
        for (Edge<std::string>* edge : vertex->getIncoming()) {
            if (excessCapacity.find(edge) != excessCapacity.end()) {
                double redistributionFactor = excessCapacity[edge] / totalExcessCapacity;
                double additionalFlow = redistributionFactor * (demand - totalInflow);
                double currentFlow = edge->getFlow();
                edge->setFlow(currentFlow + additionalFlow);
            }
        }
    }
}

double Manager::edmondsKarpWithoutNode(Graph<std::string>* res, std::string deactivated){

    Graph<std::string> graph = constructor.createGraph();

    addSupersourceAndSuperSink(graph);

    graph.findVertex(deactivated)->disable();

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

double Manager::edmondsKarpWithoutEdge(Graph<std::string>* res, std::string orig, std::string dest){

    Graph<std::string> tmp = constructor.createGraph();

    addSupersourceAndSuperSink(tmp);


    for (int i = 0; i < tmp.getNumVertex(); i++){
        if (tmp.getVertexSet()[i]->getInfo() == orig){
            for (int j = 0; j < tmp.getVertexSet()[i]->getAdj().size(); j++){
                if (tmp.getVertexSet()[i]->getAdj()[j]->getDest()->getInfo() == dest){
                    tmp.getVertexSet()[i]->getAdj()[j]->disable();
                    std::cout << orig << " to " << dest << " disabeled: " << tmp.getVertexSet()[i]->getAdj()[j]->isActivated() << std::endl;
                }
            }
        }
    }

    tmp.removeEdge("PS_4", "PS_5");
    tmp.removeEdge("PS_9", "PS_10");

    edmondsKarp(&tmp, "supersource", "supersink");

    *res = tmp;

    int maxflow = 0;
    for (int i = 0; i < tmp.getNumVertex(); i++){
        if (tmp.getVertexSet()[i]->getInfo()[0] == 'C') {
            for (int j = 0; j < tmp.getVertexSet()[i]->getIncoming().size(); j++){
                maxflow += tmp.getVertexSet()[i]->getIncoming()[j]->getFlow();
            }
        }
    }
    return maxflow;

}


void Manager::checkRemovedNode(std::string node, std::unordered_map<std::string, std::pair<int,int>>& diff){
    std::unordered_map<std::string, std::pair<int, int>> res;

    Graph<std::string> graph = constructor.createGraph();

    addSupersourceAndSuperSink(graph);

    edmondsKarp(&graph, "supersource", "supersink");


    for (int i = 0; i < graph.getNumVertex(); i++){
        std::string code = graph.getVertexSet()[i]->getInfo();
        if (code[0] != 'C') continue;

        auto vertex = graph.findVertex(code);
        int maxflow = 0;
        for (int j = 0; j < vertex->getIncoming().size(); j++){
            maxflow += graph.getVertexSet()[i]->getIncoming()[j]->getFlow();
        }
        res[code].first = maxflow;
    }

    edmondsKarpWithoutNode(&graph, node);

    for (int i = 0; i < graph.getNumVertex(); i++){
        std::string code = graph.getVertexSet()[i]->getInfo();
        if (code[0] != 'C') continue;

        auto vertex = graph.findVertex(code);
        int maxflow = 0;
        for (int j = 0; j < vertex->getIncoming().size(); j++){
            maxflow += graph.getVertexSet()[i]->getIncoming()[j]->getFlow();
        }
        res[code].second = maxflow;
    }
    diff = res;

}

void Manager::checkRemovedPipe(std::string orig, std::string dest, std::unordered_map<std::string, std::pair<int,int>>& diff){
    std::unordered_map<std::string, std::pair<int, int>> res;

    Graph<std::string> graph = constructor.createGraph();
    Graph<std::string> graph2 = constructor.createGraph();

    addSupersourceAndSuperSink(graph);

    edmondsKarp(&graph, "supersource", "supersink");

    for (int i = 0; i < graph.getNumVertex(); i++){
        std::string code = graph.getVertexSet()[i]->getInfo();
        if (code[0] != 'C') continue;

        auto vertex = graph.findVertex(code);
        int maxflow = 0;
        for (int j = 0; j < vertex->getIncoming().size(); j++){
            maxflow += graph.getVertexSet()[i]->getIncoming()[j]->getFlow();
        }
        res[code].first = maxflow;
    }


    edmondsKarpWithoutEdge(&graph2, orig, dest);

    for (int i = 0; i < graph2.getNumVertex(); i++){
        std::string code = graph2.getVertexSet()[i]->getInfo();
        if (code[0] != 'C') continue;

        auto vertex = graph2.findVertex(code);
        int maxflow = 0;
        for (int j = 0; j < vertex->getIncoming().size(); j++){
            maxflow += graph2.getVertexSet()[i]->getIncoming()[j]->getFlow();
        }
        res[code].second = maxflow;
    }
    diff = res;
}


void Manager::addSupersourceAndSuperSink(Graph<std::string>& graph){
    graph.addVertex("supersource");

    for (int i = 0; i < graph.getNumVertex(); i++) {
        if (graph.getVertexSet()[i]->getInfo()[0] == 'R')
            graph.addEdge("supersource", graph.getVertexSet()[i]->getInfo(),
                          reservoirs.at(graph.getVertexSet()[i]->getInfo()).getMaximumDelivery());

        graph.getVertexSet()[i]->enable();
    }


    graph.addVertex("supersink");

    for (int i = 0; i < graph.getNumVertex(); i++) {
        if (graph.getVertexSet()[i]->getInfo()[0] == 'C')
            graph.addEdge(graph.getVertexSet()[i]->getInfo(), "supersink",
                          cities.at(graph.getVertexSet()[i]->getInfo()).getDemand());
    }
}
