//
// Created by Davide Teixeira on 07/03/2024.
//
#ifndef DA_PROJ1_STATION_H
#define DA_PROJ1_STATION_H

#include <string>
#include "Element.h"

/**
 * @class Station
 * @brief Class representing a station.
 */
class Station : public Element {
private:
    int id; /**< Unique identifier of the station. */
public:
    /**
     * @brief Constructor for the Station class.
     * @param code Code of the station.
     * @param id Unique identifier of the station.
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    Station(std::string code, int id);

    /**
     * @brief Getter for the code of the station.
     * @return Code of the station.
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    std::string getCode();

    /**
     * @brief Getter for the unique identifier of the station.
     * @return Unique identifier of the station.
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    int getId();
};

#endif //DA_PROJ1_STATION_H