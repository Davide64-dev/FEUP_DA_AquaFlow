//
// Created by Davide Teixeira on 05/04/2024.
//

#include "Menu.h"
#include <fstream>

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
        std::cout << "5 - T3.3 - Pipe out of Comission Test" << std::endl;
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
                break;

            case 5:
                t33();
                break;


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
    std::ofstream outputFile("../2_1_edmonds_karp.csv");
    switch (option) {
        case 1:
            std::cout << "Each city" << std::endl;
            manager.edmondsKarpAllToAll(&graph);
            outputFile << "City,Code,Max Amout of Water\n";
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
                    outputFile << manager.cities.at(graph.getVertexSet()[i]->getInfo()).getName() <<
                        "," << graph.getVertexSet()[i]->getInfo() << "," << temp << '\n';
                }
            }
            std::cout << "The total Max Flow is: " << maxflow << std::endl;
            outputFile.close();
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
    std::ofstream outputFile("../2_2_difference.csv");
    outputFile << "City Code,Value\n";
    for (int i = 0; i < graph.getNumVertex(); i++){
        std::string city_name = graph.getVertexSet()[i]->getInfo();
        if (city_name[0] != 'C') continue;
        double demand = manager.cities.at(city_name).getDemand();
        double actual = 0;
        for (int j = 0; j < graph.getVertexSet()[i]->getIncoming().size(); j++){
            actual += graph.getVertexSet()[i]->getIncoming()[j]->getFlow();
        }

        if (demand > actual){
            std::cout << "-------- " << manager.cities.at(city_name).getName() << " --------" << std::endl;
            std::cout << city_name << " | Demand: " << demand << std::endl;
            std::cout << city_name << " | Delivered: " << actual <<  std::endl;
            std::cout << city_name << " | Difference: " << demand - actual << std::endl;
            outputFile << city_name << "," << demand - actual << '\n';
        }

        outputFile.close();

    }
}

void Menu::printCitiesDifferences(std::unordered_map<std::string, std::pair<int, int>>& res){

    std::cout <<  "City Code | City Name | Before Removal | After Removal\n";

    for (int i = 0; i < manager.network.getNumVertex(); i++){
        if (manager.network.getVertexSet()[i]->getInfo()[0] != 'C') continue;

        if (res[manager.network.getVertexSet()[i]->getInfo()].first == res[manager.network.getVertexSet()[i]->getInfo()].second) continue;
        std::cout << manager.network.getVertexSet()[i]->getInfo() << " | ";
        std::cout << manager.cities.at(manager.network.getVertexSet()[i]->getInfo()).getName() << " | ";
        std::cout << res[manager.network.getVertexSet()[i]->getInfo()].first << " | ";
        std::cout << res[manager.network.getVertexSet()[i]->getInfo()].second << std::endl;
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

    std::cout << "--------" << manager.reservoirs.at(node).getName() << " Reservoir--------" << std::endl;

    manager.checkRemovedNode(node, res);

    printCitiesDifferences(res);

    std::ofstream outputFile("../3_1_Reservoir_" + node + "_OutOfComission.csv");
    outputFile << "City Code,Before,After\n";

    for (int i = 0; i < manager.network.getNumVertex(); i++){
        if (manager.network.getVertexSet()[i]->getInfo()[0] != 'C') continue;

        if (res[manager.network.getVertexSet()[i]->getInfo()].first == res[manager.network.getVertexSet()[i]->getInfo()].second) continue;
        outputFile << manager.network.getVertexSet()[i]->getInfo() << "," << res[manager.network.getVertexSet()[i]->getInfo()].first << ",";
        outputFile << res[manager.network.getVertexSet()[i]->getInfo()].second << std::endl;
    }

    outputFile.close();

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

    std::cout << "--------" << node << " Pumping Station--------" << std::endl;

    manager.checkRemovedNode(node, res);

    printCitiesDifferences(res);

    std::ofstream outputFile("../3_2_PumpingStation_" + node + "_OutOfComission.csv");
    outputFile << "City Code,Before,After\n";

    for (int i = 0; i < manager.network.getNumVertex(); i++){
        if (manager.network.getVertexSet()[i]->getInfo()[0] != 'C') continue;

        if (res[manager.network.getVertexSet()[i]->getInfo()].first == res[manager.network.getVertexSet()[i]->getInfo()].second) continue;
        outputFile << manager.network.getVertexSet()[i]->getInfo() << "," << res[manager.network.getVertexSet()[i]->getInfo()].first << ",";
        outputFile << res[manager.network.getVertexSet()[i]->getInfo()].second << std::endl;
    }

    outputFile.close();

}

void Menu::t33(){
    std::unordered_map<std::string, std::pair<int, int>> res;
    std::string orig, dest;
    std::cout << "Insert Pipe Origin: ";
    std::cin >> orig;

    std::cout << "Insert Pipe Destiny: ";
    std::cin >> dest;

    manager.checkRemovedPipe(orig, dest, res);

    printCitiesDifferences(res);

    std::ofstream outputFile("../3_2_Pipe_" + orig + "To" + dest + "_OutOfComission.csv");
    outputFile << "City Code,Before,After\n";

    for (int i = 0; i < manager.network.getNumVertex(); i++){
        if (manager.network.getVertexSet()[i]->getInfo()[0] != 'C') continue;

        if (res[manager.network.getVertexSet()[i]->getInfo()].first == res[manager.network.getVertexSet()[i]->getInfo()].second) continue;
        outputFile << manager.network.getVertexSet()[i]->getInfo() << "," << res[manager.network.getVertexSet()[i]->getInfo()].first << ",";
        outputFile << res[manager.network.getVertexSet()[i]->getInfo()].second << std::endl;
    }

}

void Menu::start(){

    printIntro();

    mainMenu();
}

