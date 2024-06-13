//
// Created by Davide Teixeira on 06/03/2024.
//

#ifndef DA_PROJ1_CITY_H
#define DA_PROJ1_CITY_H

#include <string>
#include "Element.h"

/**
 * @class City
 * @brief Class representing a city.
 */
class City : public Element{

private:
    std::string name; /**< Name of the city. */
    int id; /**< Unique identifier of the city. */
    double demand; /**< Water Demand of the city. */
    long population; /**< Population of the city. */
public:

    /**
     * @brief Constructor for the City class.
     * @param name Name of the city.
     * @param id Unique identifier of the city.
     * @param code Code of the city.
     * @param demand Demand of the city.
     * @param population Population of the city.
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    City(std::string name, int id, std::string code, double demand, long population);

    /**
     * Getter for the name of the city.
     * @return Name of the City
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    std::string getName();

    /**
     * Getter for the id of the city
     * @return Id of the city
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    int getId();

    /**
     * Getter for the code of the city
     * @return Code of the city
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    std::string getCode();

    /**
     * Getter for the water demand of the city
     * @return Water demand of the city
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    double getDemand();

    /**
     * Getter for the city's population
     * @return city's population
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    long getPopulation();

};


#endif //DA_PROJ1_CITY_H
