//
// Created by anacr on 29/03/2024.
//

#include "Algorithms.h"

template <class T>
bool findPathBFS(Graph<T>& graph, std::unordered_map<T, T>& parent, T source, T sink, std::unordered_map<T, std::unordered_map<T, int>>& residual) {
    std::vector<T> bfsResult = graph.bfs(source);
    bool pathExists = std::find(bfsResult.begin(), bfsResult.end(), sink) != bfsResult.end();

    if (pathExists) {
        T v = sink;
        while (v != source) {
            for (T u : bfsResult) {
                if (residual[u][v] > 0) {
                    parent[v] = u;
                    v = u;
                    break;
                }
            }
        }
    }

    return pathExists;
}

template <class T>
int edmondsKarp(Graph<T>& graph, T source, T sink) {
    std::unordered_map<T, std::unordered_map<T, int>> residual;
    for (auto v : graph.getVertexSet()) {
        for (auto e : v->getAdj()) {
            residual[v->getInfo()][e->getDest()->getInfo()] = e->getWeight();
        }
    }

    std::unordered_map<T, T> parent;
    int max_flow = 0;

    while (findPathBFS(graph, parent, source, sink, residual)) {
        int path_flow = INT_MAX;
        for (T v = sink; v != source; v = parent[v]) {
            T u = parent[v];
            path_flow = std::min(path_flow, residual[u][v]);
        }

        for (T v = sink; v != source; v = parent[v]) {
            T u = parent[v];
            residual[u][v] -= path_flow;
            residual[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

template <class T>
void t21(Graph<T>& graph){
    int option = 0;
    std::cout << "Maximum amount of water that can reach..." << std::endl;
    std::cout << "1 - Each city" << std::endl;
    std::cout << "2 - A specific city" << std::endl;
    std::cout << "\nChoose an option:";
    std::cin >> option;

    switch (option) {
        case 1:
            std::cout << "Each city" << std::endl;
            std::cout << "TO-DO" << std::endl;
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
    std::cout << "Edmonds-Karp algorithm example" << std::endl;
    Vertex source = graph.getVertexSet()[0];
    Vertex sink = graph.network.getVertexSet()[5];
    std::cout << "Max flow: " << edmondsKarp(graph.network, source, sink) << std::endl;
}