//
// Created by Davide Teixeira on 06/03/2024.
//

#include "City.h"
#include <string>

City::City(std::string name, int id, std::string code, double demand, long population) :
            Element(code), name(name), id(id), demand(demand), population(population) {};


std::string City::getName(){
    return this->name;
}

int City::getId(){
    return this->id;
}

std::string City::getCode() {
    return this->code;
}

double City::getDemand(){
    return this->demand;
}


long City::getPopulation(){
    return this->population;
}