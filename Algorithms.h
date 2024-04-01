//
// Created by anacr on 29/03/2024.
//

#ifndef DA_PROJ1_ALGORITHMS_H
#define DA_PROJ1_ALGORITHMS_H

#include "data_structures/Graph.h"
#include "Reservoir.h"
#include "City.h"
#include "Manager.h"
#include <unordered_map>

/**
 * @brief Performs a breadth-first search (BFS) in the residual graph to find an augmenting path from the source to the sink.
 *
 * @param graph The graph on which the BFS is to be performed.
 * @param parent A map to store the parent of each vertex, along the path from the source to the sink.
 * @param source The source vertex.
 * @param sink The sink vertex.
 * @param residual The residual graph.
 *
 * @return True if there is a path from the source to the sink in the residual graph, false otherwise.
 */
template <class T>
bool findAugmentingPath(Graph<T>& graph, T source, T sink);
/**
 * @brief Implements the Edmonds-Karp algorithm to find the maximum flow from the source to the sink in a flow network.
 *
 * @param graph
 * @param source The source vertex.
 * @param sink The sink vertex.
 *
 * @return The maximum flow from the source to the sink.
 */
template <class T>
int edmondsKarp(Graph<T>& graph, std::unordered_map<std::string, Reservoir>& reservoirs, std::unordered_map<std::string, City>& cities);

/**
 * @brief Executes the T2.1 problem.
 * Determine the maximum amount of water that can reach each or a specific city (to be selected via the Menu)
 * and display it in a natural graphical format.
 *
 * @param graph The graph network.
 */
void t21(Manager manager);

#endif //DA_PROJ1_ALGORITHMS_H
