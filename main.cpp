#include <iostream>
#include <filesystem>
#include "City.h"
#include "Manager.h"
#include "Algorithms.h"

void printIntro(){
    std::cout << "+-----------------------------------+\n";
    std::cout << "|                                   |\n";
    std::cout << "|        DA PROJECT 1 - G05_2       |\n";
    std::cout << "|                                   |\n";
    std::cout << "+-----------------------------------+\n\n";
}

int main() {

    Manager manager = Manager();

    printIntro();

    // MENU
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
                t21(manager);
                break;

            default:
                std::cout << "Invalid option" << std::endl;
                break;
        }


        return 0;

    }
}
