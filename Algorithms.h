//
// Created by anacr on 29/03/2024.
//

#ifndef DA_PROJ1_ALGORITHMS_H
#define DA_PROJ1_ALGORITHMS_H

#include "data_structures/Graph.h"
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
bool findPathBFS(Graph<T>& graph, std::unordered_map<T, T>& parent, T source, T sink, std::unordered_map<T, std::unordered_map<T, int>>& residual);

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
int edmondsKarp(Graph<T>& graph, T source, T sink);

/**
 * @brief Executes the T2.1 problem.
 * Determine the maximum amount of water that can reach each or a specific city (to be selected via the Menu)
 * and display it in a natural graphical format.
 *
 * @param graph The graph network.
 */
template <class T>
void t21(Graph<T>& graph);

#endif //DA_PROJ1_ALGORITHMS_H
