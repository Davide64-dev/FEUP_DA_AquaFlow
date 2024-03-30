#include <iostream>
#include <filesystem>
#include "data_structures/graph.h"
#include "City.h"
#include "GraphConstructor.h"
#include "Manager.h"

void printIntro(){
    std::cout << "+-----------------------------------+\n";
    std::cout << "|                                   |\n";
    std::cout << "|        DA PROJECT 1 - G05_2       |\n";
    std::cout << "|                                   |\n";
    std::cout << "+-----------------------------------+\n\n";
}

int main() {

    Manager manager = Manager();
/*
    for (int i = 0; i< manager.network.getNumVertex(); i++){

        if(manager.network.getVertexSet()[i]->getInfo()[0] == 'P')
            std::cout << manager.network.getVertexSet()[i]->getInfo() << std::endl;

    }
*/

    // Create a menu to choose what option to do
    printIntro();

    int option = -1;
    while (option != 0) {

        std::cout << "\t:::: MENU ::::" << std::endl;
        std::cout << "0 - Exit" << std::endl;
        std::cout << "1 - T2.1 - Maximum amount of water that can reach each or a specific city" << std::endl;
        std::cout << "\nChoose an option:";
        std::cin >> option;

        switch (option) {
            case 0:
                std::cout << "Exiting... :)" << std::endl;
                break;

            case 1:
                std::cout << "Maximum amount of water that can reach..." << std::endl;
                std::cout << "1 - Each city" << std::endl;
                std::cout << "2 - A specific city" << std::endl;
                std::cout << "\nChoose an option:";
                std::cin >> option;

                switch (option) {
                    case 1:
                        std::cout << "Each city" << std::endl;
                        break;
                    case 2:
                        std::cout << "A specific city" << std::endl;
                        break;
                    default:
                        break;
                }

                break;

            default:
                std::cout << "Invalid option" << std::endl;
                break;
        }


        return 0;

    }
}
