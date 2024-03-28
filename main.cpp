#include <iostream>
#include <filesystem>
#include "data_structures/graph.h"
#include "City.h"
#include "GraphConstructor.h"
#include "Manager.h"

int main() {

    Manager manager = Manager();

    for (int i = 0; i< manager.network.getNumVertex(); i++){

        if(manager.network.getVertexSet()[i]->getInfo()[0] == 'P')
            std::cout << manager.network.getVertexSet()[i]->getInfo() << std::endl;

    }

    return 0;

}
