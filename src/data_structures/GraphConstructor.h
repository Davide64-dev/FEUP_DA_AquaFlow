//
// Created by Davide Teixeira on 07/03/2024.
//

#ifndef DA_PROJ1_GRAPHCONSTRUCTOR_H
#define DA_PROJ1_GRAPHCONSTRUCTOR_H

#include "Graph.h"
#include "Element.h"
#include "City.h"
#include "Station.h"
#include "Reservoir.h"
#include <unordered_map>
#include <string>

/**
 * @class GraphConstructor
 * @brief Class responsible for constructing the graph.
 */
class GraphConstructor {
private:
    std::string citiesFile; /**< File containing city data. */
    std::string reservoirsFile; /**< File containing reservoir data. */
    std::string stationsFile; /**< File containing station data. */
    std::string pipesFile; /**< File containing pipe data. */
    bool isSmallDataSet; /**< Flag indicating whether the dataset is the small one. */

    /**
     * @brief Parses a line of input to create a city object.
     * @param line Line containing city data.
     * @return City object parsed from the line.
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    City parseCity(std::string line);

    /**
     * @brief Parses a line of input to create a reservoir object.
     * @param line Line containing reservoir data.
     * @return Reservoir object parsed from the line.
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    Reservoir parseReservoir(std::string line);

    /**
     * @brief Parses a line of input to create a station object.
     * @param line Line containing station data.
     * @return Station object parsed from the line.
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    Station parseStation(std::string line);

    /**
     * @brief Adds nodes to the graph based on the parsed data.
     * @param graph Graph to which nodes will be added.
     * @par Complexity
       *   - Time: O(V)
       *   - Space: O(V)
     */
    void addNodes(Graph<Element>& graph);

    /**
     * @brief Adds edges to the graph based on the parsed data.
     * @param graph Graph to which edges will be added.
     * @par Complexity
       *   - Time: O(E)
       *   - Space: O(E)
     */
    void addEdges(Graph<Element>& graph);

public:
    /**
     * @brief Constructor for the GraphConstructor class.
     * @param citiesFile File containing city data.
     * @param reservoirsFile File containing reservoir data.
     * @param stationsFile File containing station data.
     * @param pipesFile File containing pipe data.
     * @param isSmallDataSet Flag indicating whether the dataset is small.
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    GraphConstructor(std::string citiesFile, std::string reservoirsFile, std::string stationsFile, std::string pipesFile, bool isSmallDataSet);

    /**
     * @brief Default constructor for the GraphConstructor class.
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    GraphConstructor();

    /**
     * @brief Creates a graph based on the provided data files.
     * @return Graph constructed from the provided data.
     * @par Complexity
       *   - Time: O(V + E)
       *   - Space: O(V + E)
     */
    Graph<std::string> createGraph();

    /**
     * @brief Retrieves a map of cities parsed from the data file.
     * @return Map of cities.
     * @par Complexity
       *   - Time: O(C), C: Number of Cities
       *   - Space: O(C), C: Number of Cities
     */
    std::unordered_map<std::string, City> getCityMap();

    /**
     * @brief Retrieves a map of reservoirs parsed from the data file.
     * @return Map of reservoirs.
     * @par Complexity
       *   - Time: O(R), R: Number of Reservoirs
       *   - Space: O(R), R: Number of Reservoirs
     */
    std::unordered_map<std::string, Reservoir> getReservoirMap();

    /**
     * @brief Retrieves a map of stations parsed from the data file.
     * @return Map of stations.
     * @par Complexity
       *   - Time: O(S), S: Number of Pumping Stations
       *   - Space: O(S), S: Number of Pumping Stations
     */
    std::unordered_map<std::string, Station> getStationMap();

    /**
     * @brief Parses a line of input to extract pipe data.
     * @param line Line containing pipe data.
     * @param sourc Source node of the pipe.
     * @param dest Destination node of the pipe.
     * @param weight Weight of the pipe.
     * @param direction Direction of the pipe.
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    void parsePipe(std::string line, std::string& source, std::string& dest, double& weight, int& direction);
};

#endif //DA_PROJ1_GRAPHCONSTRUCTOR_H