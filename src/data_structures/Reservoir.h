//
// Created by Davide Teixeira on 06/03/2024.
//

#ifndef DA_PROJ1_RESERVOIR_H
#define DA_PROJ1_RESERVOIR_H

#include <string>
#include "Element.h"

/**
 * @class Reservoir
 * @brief Class representing a reservoir.
 */
class Reservoir : public Element {
private:
    std::string name; /**< Name of the reservoir. */
    std::string municipality; /**< Municipality of the reservoir. */
    int id; /**< Unique identifier of the reservoir. */
    long maximum_delivery; /**< Maximum delivery the reservoir can pump. */
public:
    /**
     * @brief Constructor for the Reservoir class.
     * @param name Name of the reservoir.
     * @param municipality Municipality of the reservoir.
     * @param id Unique identifier of the reservoir.
     * @param code Code of the reservoir.
     * @param maximum_delivery Maximum delivery the reservoir can pump.
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    Reservoir(std::string name, std::string municipality, int id, std::string code, long maximum_delivery);

    /**
     * @brief Getter for the name of the reservoir.
     * @return Name of the reservoir.
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    std::string getName();

    /**
     * @brief Getter for the municipality of the reservoir.
     * @return Municipality of the reservoir.
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    std::string getMunicipality();

    /**
     * @brief Getter for the unique identifier of the reservoir.
     * @return Unique identifier of the reservoir.
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    int getId();

    /**
     * @brief Getter for the code of the reservoir.
     * @return Code of the reservoir.
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    std::string getCode();

    /**
     * @brief Getter for the maximum delivery the reservoir can pump.
     * @return Maximum delivery the reservoir can pump.
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    long getMaximumDelivery();
};

#endif //DA_PROJ1_RESERVOIR_H