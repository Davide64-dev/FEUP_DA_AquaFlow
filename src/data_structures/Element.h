//
// Created by Davide Teixeira on 07/03/2024.
//

#ifndef DA_PROJ1_ELEMENT_H
#define DA_PROJ1_ELEMENT_H

/**
 * @class Element
 * @brief Base class representing an element with a code.
 */
class Element {
protected:
    std::string code; /**< Code of the element. */
public:
    /**
     * @brief Constructor for the Element class.
     * @param code Code of the element.
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    Element(std::string code) : code(code) {}

    /**
     * @brief Equality operator for comparing elements based on their code.
     * @param other Another Element object to compare with.
     * @return True if the elements have the same code, false otherwise.
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    bool operator==(const Element& other) const {
        return this->code == other.code;
    }
};


#endif //DA_PROJ1_ELEMENT_H
