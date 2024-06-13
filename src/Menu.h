//
// Created by Davide Teixeira on 05/04/2024.
//

#ifndef DA_PROJ1_MENU_H
#define DA_PROJ1_MENU_H


#include "Manager.h"

/**
 * @class Menu
 * @brief Class for handling user interface and menu functionalities.
 */
class Menu {
private:
    Manager manager; /**< Instance of the Manager class. */

public:
    /**
     * @brief Constructor for Menu class.
     * @param manager Instance of the Manager class.
     * @par Complexity
       *   - Time: O(1)
       *   - Space: O(1)
     */
    Menu(Manager manager);

    /**
     * @brief Starts the menu system.
     * @par Complexity
        *   - Time: O(1)
        *   - Space: O(1)
     */
    void start();

    /**
     * @brief Prints the introduction message.
     * @par Complexity
        *   - Time: O(1)
        *   - Space: O(1)
     */
    void printIntro();

    /**
     * @brief Displays the main menu.
     * @par Complexity
        *   - Time: O(1)
        *   - Space: O(1)
     */
    void mainMenu();

    /**
     * @brief Performs task T2.1.
     * @par Complexity
       *   - Time: O(V * E^2)
       *   - Space: O(V + E)
     */
    void t21();

    /**
     * @brief Performs task T2.2.
     * @par Complexity
       *   - Time: O(V * E^2)
       *   - Space: O(V + E)
     */
    void t22();

    /**
     * @brief Performs task T2.3.
     * @par Complexity
       *   - Time: O(V * E^2)
       *   - Space: O(V + E)
     */
    void t23();

    /**
     * @brief Performs task T3.1.
     * @par Complexity
       *   - Time: O(V * E^2)
       *   - Space: O(V + E)
     */
    void t31();

    /**
     * @brief Performs task T3.2.
     * @par Complexity
       *   - Time: O(V * E^2)
       *   - Space: O(V + E)
     */
    void t32();

    /**
     * @brief Performs task T3.2.
     * @par Complexity
       *   - Time: O(V * E^2)
       *   - Space: O(V + E)
     */
    void t33();

    /**
     * @brief Prints differences in cities.
     * @param res Map containing differences in cities.
     * @par Complexity
       *   - Time: O(V)
       *   - Space: O(1)
    */
    void printCitiesDifferences(std::unordered_map<std::string, std::pair<int, int>>& res);
};


#endif //DA_PROJ1_MENU_H
