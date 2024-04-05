//
// Created by Davide Teixeira on 05/04/2024.
//

#include "Menu.h"

Menu::Menu(Manager manager) : manager(manager) {};

void Menu::printIntro() {
        std::cout << "+-----------------------------------+\n";
        std::cout << "|                                   |\n";
        std::cout << "|        DA PROJECT 1 - G05_2       |\n";
        std::cout << "|                                   |\n";
        std::cout << "+-----------------------------------+\n\n";
}

void Menu::mainMenu() {
    int option = -1;
    while (option != 0) {

        std::cout << "\t:::: MENU ::::" << std::endl;
        std::cout << "0 - Exit" << std::endl;
        std::cout << "1 - T2.1 - Maximum amount of water that can reach each or a specific city" << std::endl;
        std::cout << "2 - T2.2 - Water Demand vs. Actual Flow" << std::endl;
        std::cout << "3 - T3.1 - Water Reservoir Out of Comission Test" << std::endl;
        std::cout << "4 - T3.2 - Pumping Station out of Comission Test" << std::endl;
        std::cout << "\nChoose an option:";
        std::cin >> option;

        switch (option) {
            case 0:
                std::cout << "Exiting... :)" << std::endl;
                break;

            case 1:
                t21();
                break;

            case 2:
                t22();
                break;

            case 3:
                t31();
                break;

            case 4:
                t32();

            default:
                std::cout << "Invalid option" << std::endl;
                break;
        }
    }
}

void Menu::t21(){
    int option = 0;
    std::cout << "Maximum amount of water that can reach..." << std::endl;
    std::cout << "1 - Each city" << std::endl;
    std::cout << "2 - A specific city" << std::endl;
    std::cout << "\nChoose an option:";
    std::cin >> option;

    int maxflow = 0;
    Graph<std::string> graph;
    std::string selectedCity;
    switch (option) {
        case 1:
            std::cout << "Each city" << std::endl;
            manager.edmondsKarpAllToAll(&graph);
            for (int i = 0; i < graph.getNumVertex(); i++){
                if (graph.getVertexSet()[i]->getInfo()[0] == 'C') {
                    std::cout << manager.cities.at(graph.getVertexSet()[i]->getInfo()).getName() << " | " <<graph.getVertexSet()[i]->getInfo();
                    std::cout << " -> ";
                    int temp = 0;
                    for (int j = 0; j < graph.getVertexSet()[i]->getIncoming().size(); j++){
                        temp += graph.getVertexSet()[i]->getIncoming()[j]->getFlow();
                    }
                    maxflow += temp;
                    std::cout << temp << std::endl;
                }
            }
            std::cout << "The total Max Flow is: " << maxflow << std::endl;
            break;
        case 2:
            std::cout << "A specific city - Select Your City: ";
            std::cin >> selectedCity;
            manager.edmondsKarpAllToAll(&graph);
            for (int i = 0; i < graph.getNumVertex(); i++){
                if (graph.getVertexSet()[i]->getInfo() == selectedCity) {
                    std::cout << manager.cities.at(graph.getVertexSet()[i]->getInfo()).getName() << " | " <<graph.getVertexSet()[i]->getInfo();
                    std::cout << " -> ";
                    int temp = 0;
                    for (int j = 0; j < graph.getVertexSet()[i]->getIncoming().size(); j++){
                        temp += graph.getVertexSet()[i]->getIncoming()[j]->getFlow();
                    }
                    std::cout << temp << std::endl;
                }
            }
            break;
        default:
            std::cout << "Invalid option" << std::endl;
            break;
    }
}

void Menu::t22(){
    Graph<std::string> graph;
    manager.edmondsKarpAllToAll(&graph);
    for (int i = 0; i < graph.getNumVertex(); i++){
        std::string city_name = graph.getVertexSet()[i]->getInfo();
        if (city_name[0] != 'C') continue;
        double demand = manager.cities.at(city_name).getDemand();
        double actual = 0;
        for (int j = 0; j < graph.getVertexSet()[i]->getIncoming().size(); j++){
            actual += graph.getVertexSet()[i]->getIncoming()[j]->getFlow();
        }

        if (demand > actual){
            std::cout << city_name << " | Demand: " << demand << std::endl;
            std::cout << city_name << " | Delivered: " << actual <<  std::endl;
            std::cout << city_name << " | Difference: " << demand - actual << std::endl;
        }

    }
}

void Menu::t31(){
    std::unordered_map<std::string, std::pair<int, int>> res;
    std::string node;
    std::cout << "Insert Reservoir Code: ";
    std::cin >> node;
    if (node[0] != 'R'){
        std::cout << "Invalid Reservoir Name\n";
        return;
    }
    manager.checkRemovedNode(node, res);

    for (int i = 0; i < manager.network.getNumVertex(); i++){
        if (manager.network.getVertexSet()[i]->getInfo()[0] != 'C') continue;
        std::cout << manager.network.getVertexSet()[i]->getInfo() << " ";
        std::cout << res[manager.network.getVertexSet()[i]->getInfo()].first << " ";
        std::cout << res[manager.network.getVertexSet()[i]->getInfo()].second << std::endl;
    }
}

void Menu::t32(){

    std::unordered_map<std::string, std::pair<int, int>> res;
    std::string node;
    std::cout << "Insert Pumping Station Code: ";
    std::cin >> node;
    if (node[0] != 'P'){
        std::cout << "Invalid Pumping Station Name\n";
        return;
    }
    manager.checkRemovedNode(node, res);

    for (int i = 0; i < manager.network.getNumVertex(); i++){
        if (manager.network.getVertexSet()[i]->getInfo()[0] != 'C') continue;
        std::cout << manager.network.getVertexSet()[i]->getInfo() << " ";
        std::cout << res[manager.network.getVertexSet()[i]->getInfo()].first << " ";
        std::cout << res[manager.network.getVertexSet()[i]->getInfo()].second << std::endl;
    }

}

void Menu::start(){

    printIntro();

    mainMenu();
}

