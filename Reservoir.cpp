//
// Created by Davide Teixeira on 06/03/2024.
//

#include "Reservoir.h"

Reservoir::Reservoir(std::string name, std::string municipaly, int id, std::string code, long maximum_delivery) :
    Element(code), name(name), municipaly(municipaly), id(id), maximum_delivery(maximum_delivery) {};

std::string Reservoir::getName(){
    return this->name;
}

std::string Reservoir::getMunicipaly(){
    return this->municipaly;
}

int Reservoir::getId(){
    return this->id;
}

std::string Reservoir::getCode(){
    return this->code;
}


long Reservoir::getMaximumDelivery(){
    return this->maximum_delivery;
}