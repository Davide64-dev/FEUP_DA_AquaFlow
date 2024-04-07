//
// Created by Davide Teixeira on 08/03/2024.
//

#ifndef DA_PROJ1_MANAGER_H
#define DA_PROJ1_MANAGER_H

#include <string>
#include "data_structures/Graph.h"
#include <unordered_map>
#include "data_structures/City.h"
#include "data_structures/Reservoir.h"
#include "data_structures/Station.h"
#include "data_structures/GraphConstructor.h"

/**
 * @class Manager
 * @brief Class for managing network flow operations.
 */
class Manager {
private:
    std::string name; /**< Name of the manager. */
    GraphConstructor constructor; /**< Graph constructor instance. Responsible for constructing the graph */
public:
    Graph<std::string> network; /**< Network graph. */
    std::unordered_map<std::string, City> cities; /**< Map of cities. Maps the code to the city */
    std::unordered_map<std::string, Reservoir> reservoirs; /**< Map of reservoirs. Maps the code to the reservoir*/
    std::unordered_map<std::string, Station> stations; /**< Map of stations. Maps the code to the station*/

    /**
     * @brief Constructor for Manager class.
     * @param isSmallDataSet Flag indicating whether the dataset is the small one.
     * @param name Name of the manager.
     * @par Complexity
       *   - Time: O(V+E)
       *   - Space: O(V+E)
    */
    Manager(bool isSmallDataSet = true, std::string name = "FEUPAquaFlow");

    /**
     * @brief Tests and visits a vertex during BFS traversal for finding augmenting paths.
     * @param q Queue for BFS traversal.
     * @param e Edge being considered.
     * @param w Vertex being visited.
     * @param residual Residual capacity of the edge.
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
    */
    void testAndVisit(std::queue< Vertex<std::string>*> &q, Edge<std::string> *e, Vertex<std::string> *w, double residual);


    /**
     * @brief Finds an augmenting path in the graph using BFS.
     * @param g Pointer to the graph.
     * @param s Source vertex.
     * @param t Target vertex.
     * @return True if an augmenting path is found, false otherwise.
     * @par Complexity
       *   - Time: O(V + E)
       *   - Space: O(V)
    */
    bool findAugmentingPath(Graph<std::string> *g, Vertex<std::string> *s, Vertex<std::string> *t);


    /**
     * @brief Finds the minimum residual capacity along the augmenting path.
     * @param s Source vertex.
     * @param t Target vertex.
     * @return Minimum residual capacity.
     * @par Complexity
       *   - Time: O(n) - n is the number of edges distance between s and t
       *   - Space: O(1)
    */
    double findMinResidualAlongPath(Vertex<std::string> *s, Vertex<std::string> *t);

    /**
     * @brief Augments flow along the augmenting path.
     * @param s Source vertex.
     * @param t Target vertex.
     * @param f Flow to augment.
     * @par Complexity
       *   - Time: O(n) - n is the number of edges distance between s and t
       *   - Space: O(1)
    */
    void augmentFlowAlongPath(Vertex<std::string> *s, Vertex<std::string> *t, double f);

    /**
     * @brief Applies the Edmonds-Karp algorithm to find maximum flow from a source to a target.
     * @param g Pointer to the graph.
     * @param source Source node.
     * @param target Target node.
     * @par Complexity
       *   - Time: O(V * E^2)
       *   - Space: O(V + E)
     */
    void edmondsKarp(Graph<std::string> *g, std::string source, std::string target);

    /**
     * @brief Applies the Edmonds-Karp algorithm to find maximum between all reservoirs (source) and all cities (target).
     *  Creates a supersource and a supertarget to do it.
     * @param res Pointer to the residual graph.
     * @return Total flow from all sources to all sinks.
     * @par Complexity
       *   - Time: O(V * E^2)
       *   - Space: O(V + E)
     */
    double edmondsKarpAllToAll(Graph<std::string>* res);

    /**
     * @brief Checks the differences between the total edmonds karp and the edmonds karp with a deactivate node
     * @param node Node to deactivate.
     * @param diff Map that maps the difference of flows for each city before and after the deactivation of the node
     * @par Complexity
       *   - Time: O(V * E^2)
       *   - Space: O(V + E)
    */
    void checkRemovedNode(std::string node, std::unordered_map<std::string, std::pair<int,int>>& diff);

    /**
     * @brief Do the edmonds karp with a deactivated node
     * @param res Resulting graph after the edmonds karp
     * @param deactivated Node to deactivate
     * @return Returns the final maxflow with the deactivated node
     * @par Complexity
       *   - Time: O(V * E^2)
       *   - Space: O(V + E)
     */
    double edmondsKarpWithoutNode(Graph<std::string>* res, std::string deactivated);

    /**
     * @brief Do the edmonds karp with a deactivated edge
     * @param res  Resulting graph after the edmonds karp
     * @param orig Origin of the edge to deactivate
     * @param dest Destiny of the edge to deactivate
     * @return Returns the final maxflow with the deactivated edge
     * @par Complexity
       *   - Time: O(V * E^2)
       *   - Space: O(V + E)
    */
    double edmondsKarpWithoutEdge(Graph<std::string>* res, std::string orig, std::string dest);

    /**
     * @brief Checks the differences between the total edmonds karp and the edmonds karp with a deactivate edge
     * @param orig Origin of the edge to deactivate
     * @param dest Destiny of the edge to deactivate
     * @param diff Map that maps the difference of flows for each city before and after the deactivation of the edge
     * @par Complexity
       *   - Time: O(V * E^2)
       *   - Space: O(V + E)
     */
    void checkRemovedPipe(std::string orig, std::string dest, std::unordered_map<std::string, std::pair<int,int>>& diff);

    /**
     * @brief Adds a supersource and supersink to the graph. Connects supersource to each reservoir. Also connects each
     *  city to the supersink
     * @param graph Graph to modify.
     * @par Complexity
       *   - Time: O(V)
       *   - Space: O(1)
     */
    void addSupersourceAndSuperSink(Graph<std::string>& graph);
};


#endif //DA_PROJ1_MANAGER_H
